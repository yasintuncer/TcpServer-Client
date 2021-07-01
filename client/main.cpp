#include <QCoreApplication>
#include"client.h"
int main(int argc, char *argv[])
{
    client a;

    if(!a.connected())
        return 0;
    for(;;)
    {
        a.send_data();
        a.read_data();
        a.closeSocket();
        a.reconnect();
    }


}
