// made by GPT cuase I am lazy
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstring>
#include <functional>
#include "src/event_system/event_system.hpp"

using namespace event_system;

// Simple task to be executed when the pipe is triggered
void task_handler(void *return_ptr, void *param_ptr)
{
    const std::string *message = static_cast<const std::string *>(param_ptr);
    std::cout << "Received task: " << *message << std::endl;
}

int main()
{
    // Create a pipe
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1)
    {
        perror("Pipe creation failed");
        return 1;
    }

    // Create a listener to monitor the pipe's read end
    listener event_listener;

    // Create a task and assign it to the pipe's read end
    LEVEL urgency = LEVEL::SOME;
    LEVEL importance = LEVEL::VERY;
    std::string message_str = "Hello, Pipe!";
    task pipe_task(task_handler, nullptr, &message_str, urgency, importance, 1);

    // Register the event for the pipe's read end (pipe_fd[0])
    event_listener.add_event(pipe_fd[0], EPOLLIN, pipe_task);

    // Write data to the pipe (this will trigger the task in the event system)
    const char *message = "Hello, Event System!";
    if (write(pipe_fd[1], message, strlen(message)) == -1)
    {
        perror("Write to pipe failed");
        return 1;
    }

    std::cout << "Data written to pipe: " << message << std::endl;

    // Start the event listener
    event_listener.start();

    // Allow time for the listener to process the event (this could be improved with a more robust wait mechanism)
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // Stop the listener after the task runs once
    event_listener.stop();

    // Close the pipe
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    return 0;
}
