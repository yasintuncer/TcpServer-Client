#include "server.h"
#include<fcntl.h>


#define DEFAULT_PORT 1234
#define MAX_QUEUE 5
#define DEFAULT_BUFFER_SIZE 4096

static inline bool setSocketblockingState(int fd, bool blocking)
{
    if(fd < 0)
        return false;
    int flags = fcntl(fd, F_GETFL, 0);
    flags = (blocking ? (flags & ~O_NONBLOCK): (flags | O_NONBLOCK));
    return ((fcntl(fd,F_SETFL,flags)== 0) ? true:false);
}
Server::Server()
{

    netparams.port = DEFAULT_PORT;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        std::cerr << "Error Openning socket ( " << errno << ") : " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof (sockaddr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(netparams.port);

    // bind socket
    int retval = bind(sockfd, reinterpret_cast<struct sockaddr *>(&server_addr), sizeof (server_addr));
    if(retval < 0)
    {
        std::cerr << "Error in binding socket (" << errno << " :)" << strerror(errno) << std::endl;
        server_addr.~sockaddr_in();
        exit(EXIT_FAILURE);
    }

   // setSocketblockingState(sockfd,false);
    listen(sockfd, MAX_QUEUE);
}

const char* Server::Accept()
{
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(struct sockaddr_in);
    newsockfd = accept(sockfd, reinterpret_cast<struct sockaddr *>(&client_addr), &client_len);
    if (newsockfd < 0)
    {
        if (errno != EAGAIN && errno != EWOULDBLOCK)
        {

            client_addr.~sockaddr_in();
            close(newsockfd);
            perror("Error on accept");
        }
        else
            return nullptr;
    }
    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(client_addr.sin_addr), str, INET6_ADDRSTRLEN);
    incoming_ip = str;
    std::cout << "Connected Device İP : " << incoming_ip << std::endl;
    return incoming_ip.c_str();

}

int Server::read_data()
{char  buffer[1024];

    int retval = recv(newsockfd,buffer, 256,0);
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
            temp = recv(newsockfd,buffer + retval, 256,0);
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
    std::cout << "Client :\t " << buffer << std::endl;
    return retval;
}


int Server::send_data()
{
   std::string b = "Hello";

   int retval = 0;
   retval = write(newsockfd,b.c_str(),5);

   return retval;
}

void Server::closeSocket()
{
    close(sockfd);
    close(newsockfd);
}
