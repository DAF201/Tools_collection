#include <iostream>
#include <string>
#include <conio.h>
#include <stdio.h>

using namespace std;

string execute(string command)
{
    char pipe_buffer[128];
    string execution_result = "";
    FILE *pipe = _popen(command.c_str(), "r");

    if (!pipe)
    {
        return "popen failed!";
    }

    while (!feof(pipe))
    {
        if (fgets(pipe_buffer, 128, pipe) != NULL)
            execution_result += pipe_buffer;
    }

    _pclose(pipe);
    return execution_result;
}

int main()
{
    string test = execute("ping 8.8.8.8");
    printf(test.c_str());
    // _getch();//to stop program from closing after closing
}
/*
Pinging 8.8.8.8 with 32 bytes of data:
Reply from 8.8.8.8: bytes=32 time=392ms TTL=114
Reply from 8.8.8.8: bytes=32 time=3ms TTL=114  
Reply from 8.8.8.8: bytes=32 time=3ms TTL=114
Reply from 8.8.8.8: bytes=32 time=4ms TTL=114

Ping statistics for 8.8.8.8:
    Packets: Sent = 4, Received = 4, Lost = 0 (01300ss),
Approximate round trip times in milli-seconds:
    Minimum = 3ms, Maximum = 392ms, Average = 100ms     
*/
