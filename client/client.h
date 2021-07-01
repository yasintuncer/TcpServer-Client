#ifndef CLIENT_H
#define CLIENT_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

class client
{
public:
    client();
    ~client(){closeSocket();}
    void closeSocket();
    bool connected();
    bool reconnect();
    bool isconnected;
    int send_data();
    int read_data();
    int sockfd = 0;
    int portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;


};

#endif // CLIENT_H
