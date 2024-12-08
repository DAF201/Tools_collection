// made by GTP cause I am lazy, added another pipe to show effect of priority
#include "src/event_system/event_system.hpp"
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <cstring>
using namespace event_system;
// Simple task handler that will display the priority
void task_handler(void* return_ptr, void* param_ptr)
{
    const std::string* message = static_cast<const std::string*>(param_ptr);
    int* priority = static_cast<int*>(return_ptr);

    // Display task execution and its priority
    std::cout << "Task executed with priority: " << *priority << ". Message: " << *message << std::endl;
}

int main()
{
    // Create two pipes for two different events
    int pipe_fd_1[2], pipe_fd_2[2];
    if (pipe(pipe_fd_1) == -1 || pipe(pipe_fd_2) == -1)
    {
        perror("Pipe creation failed");
        return 1;
    }

    // Create a listener to manage events
    event_system::listener event_listener;

    // Create tasks with different priorities for both pipes
    LEVEL urgency_1 = LEVEL::NOT;
    LEVEL importance_1 = LEVEL::NOT;
    std::string message_str_1 = "Hello from Pipe 1!";
    int priority_1 = priority_calculator(urgency_1, importance_1);  // Calculate priority for task 1
    task pipe_task_1(task_handler, &priority_1, &message_str_1, urgency_1, importance_1, 1);

    LEVEL urgency_2 = LEVEL::VERY;
    LEVEL importance_2 = LEVEL::SOME;
    std::string message_str_2 = "Hello from Pipe 2!";
    int priority_2 = priority_calculator(urgency_2, importance_2);  // Calculate priority for task 2
    task pipe_task_2(task_handler, &priority_2, &message_str_2, urgency_2, importance_2, 1);

    // Register the events for both pipes' read ends (pipe_fd_1[0] and pipe_fd_2[0])
    event_listener.add_event(pipe_fd_1[0], EPOLLIN, pipe_task_1);
    event_listener.add_event(pipe_fd_2[0], EPOLLIN, pipe_task_2);

    // Write data to both pipes (this will trigger the tasks in the event system)
    const char* message_1 = "Triggering Pipe 1";
    if (write(pipe_fd_1[1], message_1, std::strlen(message_1)) == -1)
    {
        perror("Write to pipe 1 failed");
        return 1;
    }
    std::cout << "Data written to pipe 1: " << message_1 << std::endl;

    const char* message_2 = "Triggering Pipe 2";
    if (write(pipe_fd_2[1], message_2, strlen(message_2)) == -1)
    {
        perror("Write to pipe 2 failed");
        return 1;
    }
    std::cout << "Data written to pipe 2: " << message_2 << std::endl;

    // Start the event listener to listen for events
    event_listener.start();

    // Allow time for the listener to process the events
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // Stop the listener after the tasks have been processed
    event_listener.stop();

    // Close the pipes
    close(pipe_fd_1[0]);
    close(pipe_fd_1[1]);
    close(pipe_fd_2[0]);
    close(pipe_fd_2[1]);

    return 0;
}
