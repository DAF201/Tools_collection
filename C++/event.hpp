/*
NOT BEING TESTED YET!
 */

#include <sys/epoll.h>
#include <map>
#include <stdio.h>
#include <thread>
#include <vector>
#include <queue>
#include <semaphore.h>
#include <chrono>
#include <time.h>
#include <signal.h>

namespace EVENT
{

#define EVENTS_MAX 1024

    // save some tokens for buffer, but does not allows the excessive amount of traffic to pass through after runs out of tokens
    class token_bucket
    {
    private:
        sem_t token;
        int current_token;
        int max_token;
        int alive = 1;
        std::thread token_gen_thread;
        void generate_token()
        {
            while (alive)
            {
                // if bucket full, sleep, else generate tokens
                while (alive && (current_token >= max_token))
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                sem_post(&token);
            }
        }

    public:
        token_bucket(int max_token)
        {
            sem_init(&token, 0, max_token);
            this->max_token = max_token;
            this->current_token = max_token;
            this->token_gen_thread = std::thread(&generate_token);
        }

        inline int get_token()
        {
            sem_wait(&token);
            current_token--;
        }

        ~token_bucket()
        {
            sem_destroy(&token);
        }
    };

    // a void function with (target_file_descriptor, handler_parameter, return_address) as arguements to handle an event
    typedef void (*event_handler)(int fd, volatile void *param, void *return_address);

    struct task
    {
        time_t arrival_time;
        int priority;
        int fd;
        event_handler *event_handler_func;
        volatile void *event_handler_args;
        void *event_handler_return;

        void exec()
        {
            (*event_handler_func)(fd, event_handler_args, event_handler_return);
        }

        bool operator<(const task &other) const
        {
            return priority != other.priority ? priority < other.priority : arrival_time > other.arrival_time;
        }

        bool operator>(const task &other) const
        {
            return priority != other.priority ? priority > other.priority : arrival_time < other.arrival_time;
        }
    };

#define EVENTS_MAX 1024

    volatile int listener_alive = 1;

    class event_worker
    {
    private:
        std::thread worker_thread;
        std::queue<int> *events_list;
        std::map<int, task> *events_handler_map;
        sem_t *task_sem;

        void work() noexcept
        {
            int fd;
            while (listener_alive)
            {
                if (events_list->empty())
                {
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
                else
                {
                    fd = events_list->front();
                    events_list->pop();
                    try
                    {
                        events_handler_map->at(fd).exec();
                    }
                    catch (const std::exception &e)
                    {
                        printf("error occur while handling: %d\nerror description: %s", fd, e.what());
                    }
                }
            }
        }

    public:
        event_worker() {};
        event_worker(std::queue<int> *events_list, std::map<int, task> *events_handler_map, sem_t *task_sem)
        {
            this->events_list = events_list;
            this->events_handler_map = events_handler_map;
            this->task_sem = task_sem;
        }

        void start()
        {
            this->worker_thread = std::thread(&event_worker::work);
        }
    };

    class event_listener
    {
    private:
        int epoll_fd;
        int num_of_events;

        std::thread listener_thread;

        // save next event to handle
        std::queue<int> events_list;
        // save how to handle
        std::map<int, task> events_handler_map;

        epoll_event ev;
        epoll_event events_buffer[EVENTS_MAX];

        event_worker ew;

        sem_t task_sem;

        static void epoll_signal_handler(int signal)
        {
            listener_alive = 0;
        }

    public:
        event_listener()
        {
            epoll_fd = epoll_create1(0);

            signal(SIGUSR1, event_listener::epoll_signal_handler);

            sem_init(&task_sem, 0, 1);

            this->ew = event_worker(&events_list, &events_handler_map, &task_sem);

            ew.start();
        }

        void event_add(int fd, int event_listening, event_handler *eh, int priority = 0, void *args_ptr, void *return_ptr)
        {
            sem_wait(&task_sem);
            ev.data.fd = fd;
            ev.events = event_listening;
            epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev);
            // save how to handle a event for file descriptor fd
            events_handler_map[fd] = {time(nullptr), priority, fd, eh, args_ptr, return_ptr};
            sem_post(&task_sem);
        }

        void event_del(int fd)
        {
            sem_wait(&task_sem);
            epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, &ev);
            events_handler_map.erase(fd);
            sem_post(&task_sem);
        }

        void listen()
        {
            while (listener_alive)
            {
                num_of_events = epoll_wait(epoll_fd, events_buffer, EVENTS_MAX, -1);

                for (int i = 0; i < num_of_events; ++i)
                {
                    sem_wait(&task_sem);
                    events_list.push(events_buffer->data.fd);
                    sem_post(&task_sem);
                }
            }
        }

        // Start the listener in a separate thread
        void start()
        {
            listener_thread = std::thread(&event_listener::listen, this);
        }

        // Stop the listener (interrupt epoll_wait)
        void stop()
        {
            kill(getpid(), SIGUSR1); // Send signal to stop epoll_wait
            listener_thread.join();  // Ensure the listener thread finishes before exiting
        }

        ~event_listener()
        {
            if (listener_thread.joinable())
            {
                listener_thread.join();
            }
            sem_destroy(&task_sem);
        }
    };
}
