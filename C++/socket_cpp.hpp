#include <WinSock2.h>
#include <stdio.h>
#include <string>
#include <thread>
#include <vector>
#include <windows.h>
#define MAX_LENGTH 896
using namespace std;
class cpp_socket
{
public:
    cpp_socket(string server_ip, int server_port)
    {
        sock_version = MAKEWORD(2, 2);

        if (WSAStartup(sock_version, &WSA_data) != 0)
        {
            printf("%s", "WSAStartup error\n");
            return;
        }

        client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (client_socket == INVALID_SOCKET)
        {
            printf("%s", "error when creating socket\n");
            return;
        }

        server_address.sin_family = AF_INET;
        server_address.sin_port = server_port;
        server_address.sin_port = htons(920);
        server_address.sin_addr.s_addr = inet_addr(server_ip.c_str());

        if (connect(client_socket, (sockaddr *)&server_address, sizeof(server_address)) == SOCKET_ERROR)
        {
            printf("%s", "connecting error\n");
            return;
        }
        // start two threads to recv and send
        recv_thread = thread(&cpp_socket::recv_package, this);
        send_thread = thread(&cpp_socket::send_package, this);
        printf("%s", "socket created\n");
    }
    char *c_recv()
    {
        // get the last element(earliest) in vector, and remove it
        char *data = recv_buffer.back();
        recv_buffer.pop_back();
        return data;
    }

    void c_send(void *data)
    {
        // insert to begin of the vector
        send_buffer.push_back((char *)data);
        return;
    }

private:
    SOCKET client_socket;
    WORD sock_version;
    WSADATA WSA_data;
    sockaddr_in server_address;
    vector<char *> recv_buffer;
    vector<char *> send_buffer;
    thread recv_thread;
    thread send_thread;

    void recv_package()
    {
        char buffer[1024];
        while (1)
        {
            // recieve something
            recv(client_socket, buffer, sizeof(buffer), 0);
            // printf("%s", buffer);

            // CRUSHED HERE TODO:FIX

            // inert it to begin of the vector
            recv_buffer.insert(recv_buffer.begin(), buffer);
            Sleep(100);
        }
    }

    void send_package()
    {
        while (1)
        {
            // something need to be send
            if (send_buffer.size() != 0)
            {
                // get the last element of send vector
                char *data = send_buffer.back();
                // remove that
                send_buffer.pop_back();
                // send
                send(client_socket, data, strlen(data), 0);
                Sleep(100);
            }
        }
    }
};
