#ifndef CPP_CLIENT_H
#define CPP_CLIENT_H

#include <string>
#include <string.h>
#include <vector>
#include <cstddef>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>

class cpp_client
{
public:
    int sockfd;
    struct sockaddr host_name;
    struct addrinfo hints;
    struct addrinfo *servinfo;
    std::vector<char> data;

    cpp_client(const char* host_name, int port);
    void read_data();
    void send_ack();
    ~cpp_client();
};

#endif // CPP_CLIENT_H
