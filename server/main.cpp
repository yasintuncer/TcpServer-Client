#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    bool isConnected = false;

    Server tcp;
    for(;;)
    {
        int a = 0;
        if(!tcp.Accept() && !isConnected)
        {
            if((a % 1000) == 0)
            {
                std::cout << "No pending Connections" <<std::endl;
            }
            continue;
        }
        isConnected = true;
        if(tcp.read_data()< 0)
        {
            //break;
        }
        tcp.send_data();
    }

    std::cout << "Exiting NOW\n";

    close(tcp.newsockfd);
    close(tcp.sockfd);



    return 0;
}
