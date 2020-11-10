#include "cpp_client.h"
#include <iostream>
#include <poll.h>

cpp_client::cpp_client(const char* host_name, int port)
{
    int status;
    //necessary or you get error: ai_socktype not supported
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    const char* c_port = std::to_string(port).c_str();
    if ((status = getaddrinfo(host_name, c_port, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

    int yes=1;
    if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof yes) == -1) {
        perror("setsockopt");
        exit(1);
    }

    connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);
}

void cpp_client::read_data()
{
    struct pollfd receiving[1];
    receiving[0].fd = sockfd;
    receiving[0].events = POLLIN;

    while (true)
    {
        int in_poll = poll(receiving, 1, 1000);
        if(in_poll == 0)
        {
            std::cout << "receiving poll timed out\n";
            return;
        }
        else
        {
            int iter = 0;
            int length = 0;
            int start_index = 0;
            while(true){
                iter++;
                char* char_data;
                char_data = new char[1024];
                int stat = recv(sockfd, char_data, 1024, 0);
                if(stat == -1){
                    std::cout << "error receiving data\n";
                    return;
                }
                if(stat == 0){
                    std::cout << "server closed connection\n";
                    return;
                }
                int index = 0;
                bool end_char_found = false;
                char* delimiter = strchr(char_data, ':');
                if(delimiter != nullptr)
                {
                    index = delimiter - char_data;
                    char c_length[index];
                    strncpy(c_length, char_data, index);
                    length = atoi(c_length);
                    std::cout << "length: " << length << '\n';
                    if(length == 3)
                    {
                        std::string string(char_data, 5);
                        std::string end_string = string.substr(2,3);
                        if(end_string.compare("END") == 0)
                        {
                            std::cout << "END\n";
                            return;
                        }
                    }
                    start_index = index + 1;
                }
                for(int i = start_index; i < stat; i++)
                {
                    if (char_data[i] == '0')
                    {
                        end_char_found = true;
                        std::cout << "found end char\n";
                        break;
                    }
                    data.push_back(char_data[i]);
//                    std::cout << char_data[i] << '\n';
                }

                if(end_char_found)
                {
                    break;
                }
                free(char_data);
            }
        }
        send_ack();

    }
}

void cpp_client::send_ack()
{
    struct pollfd sending[1];
    sending[0].fd = sockfd;
    sending[0].events = POLLOUT;

    std::string msg = "Received";
    const char* c_msg = msg.c_str();
    int len = strlen(c_msg);
    int out_poll = poll(sending, 1, 4000);
    if(out_poll == 0)
    {
        std::cout << "sending poll timed out\n";
    }
    else
    {
        int stat = send(sockfd, c_msg, len, 0);
        if(stat == -1){
            std::cout << "error sending data\n";
        }
    }
}


cpp_client::~cpp_client()
{
    freeaddrinfo(servinfo);
}
