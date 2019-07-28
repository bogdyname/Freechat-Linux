/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "peerin.h"

Peerin::Peerin(ConnectionF2F *parent)
    : QTcpServer(parent)
{

}

void Peerin::PassOnMyIpAddress()
{
    PassOnWANIp(strPassOnWANip);

    return;
}

void Peerin::CheckPortsForConnection()
{
    if(listen(QHostAddress::Any, 1234))
        {
            #ifndef Q_DEBUG
            qDebug() << "Server: started";
            #endif
        }
        else
        {
            #ifndef Q_DEBUG
            qDebug() << "Server: not started!";
            #endif
        }

    return;
}

void Peerin::Connection()
{
    Peerout *peer = new Peerout();
    peer->DoConnect();

    return;
}
