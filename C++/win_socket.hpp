#include <WinSock2.h>
#include <stdio.h>
#include <string>
#include <thread>
#include <queue>
#include <windows.h>
#define MAX_LENGTH 896
using namespace std;
struct send_pkg
{
    void *data;
    int size;
};
class cpp_socket
{
public:
    cpp_socket(string server_ip, int server_port)
    {
        sock_version = MAKEWORD(2, 2);

        if (WSAStartup(sock_version, &WSA_data) != 0)
        {
            printf("%s", "WSAStartup error\n");
            exit(-1);
        }

        client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (client_socket == INVALID_SOCKET)
        {
            printf("%s", "error when creating socket\n");
            exit(-1);
        }

        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(server_port);
        server_address.sin_addr.s_addr = inet_addr(server_ip.c_str());

        if (connect(client_socket, (sockaddr *)&server_address, sizeof(server_address)) == SOCKET_ERROR)
        {
            printf("%s", "connecting error\n");
            exit(-1);
        }

        // LIE thread header used unix lib, so dont work here

        RECV_THREAD = thread(&cpp_socket::RECVING, this);
        SEND_THREAD = thread(&cpp_socket::SENDING, this);

        printf("%s", "socket created\n");
    }
    void S_send(void *data, int size)
    {
        send_pkg new_pkg = {data, size};
        send_queue.push(new_pkg);
    };
    void *S_recv()
    {
        if (!recv_queue.empty())
        {
            void *data = recv_queue.front();
            recv_queue.pop();
            return data;
        }
        return nullptr;
    };

private:
    SOCKET client_socket;
    WORD sock_version;
    WSADATA WSA_data;
    sockaddr_in server_address;
    thread RECV_THREAD;
    thread SEND_THREAD;
    queue<void *> recv_queue;
    queue<send_pkg> send_queue;

    void SENDING()
    {
        send_pkg data;
        while (true)
        {
            if (!send_queue.empty())
            {
                data = send_queue.front();
                send_queue.pop();
                send(client_socket, (const char *)data.data, data.size, 0);
                Sleep(100);
            }
        }
    }
    void RECVING()
    {
        char buffer[1024];
        while (true)
        {
            recv(client_socket, buffer, 1024, 0);
            recv_queue.push(buffer);
        }
    }
};
