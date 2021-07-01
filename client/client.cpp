#include "client.h"
#include <iostream>
#include <vector>
client::client()
{
    portno = 1234;


    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        std::cout << "Error Open Socket" << std::endl;
        exit(EXIT_FAILURE);
    }
    server = gethostbyname("192.168.2.27");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);

}

bool client::connected()
{
    int retval = 0;
    int n_times = 10;
    do
    {
        retval = connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
        if(retval >= 0)
            break;
    }while(n_times --);

    if ( retval< 0)
    {
        std::cout << "ERROR connecting" << std::endl;

        return false;
    }
    std::cout << "Connected Host" << std::endl;

    isconnected = true;
    return true;
}

int client::send_data()
{

       std::string b = "Hello";
       getline (std::cin, b);
       int retval = 0;
       retval = write(sockfd,b.c_str(),5);

       return retval;

}

int client::read_data()
{
    char  buffer[1024];

    int retval = recv(sockfd,buffer, 256,0);
    if(retval <0)
    {
        std::cerr << "Read Error on Socket !" << std::endl;
        return retval;
    }
    else if(retval == 256)
    {
        int temp = 0;
        for(;;)
        {
            temp = recv(sockfd,buffer + retval, 256,0);
            if(temp <0)
            {
                std::cerr << "Read Error on Socket !" << std::endl;
                return retval;
            }
            retval += temp;
            if(temp == 0 || temp < 256)
            {
                break;
            }

        }
    }


    std::cout << "Received Data Size:" << retval << std::endl;
    std::cout << "Server :\t " << buffer << std::endl;
    return retval;

}


void client::closeSocket()
{
    close(sockfd);
    isconnected = false;
    std::cout << "Disconnected Server" << std::endl;
}

bool client::reconnect()
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        std::cout << "Error Open Socket" << std::endl;
        exit(EXIT_FAILURE);
    }
    return connected();

}
