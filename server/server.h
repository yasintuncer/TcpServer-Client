#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> //sockaddr, socklen_t
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>


struct TcpNetParams
{
    std::string server_ip;
    uint16_t port;
};


class Server
{
public:
    Server();
    ~Server(){closeSocket();}
    void closeSocket();
    int read_data();
    int send_data();
    const char *Accept();
    TcpNetParams netparams;
    int sockfd;
    int newsockfd;
    std::string incoming_ip;


};

#endif // SERVER_H
