/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "peerin.h"

Peerin::Peerin(QObject *parent)
    : QTcpServer(parent)
{
    CheckPortForConnection();

}

void Peerin::CheckPortForConnection()
{
    server = new QTcpServer(this);

        if(listen(QHostAddress::Any, 80))
        {
           #ifndef Q_DEBUG
           qDebug() << "Server: started";
           #endif
        }
        else
        {
            #ifndef Q_DEBUG
            qDebug() << "Server: not started: " << errorString();
            #endif
        }

    return;
}

void Peerin::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *socket = new QTcpSocket();
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, SIGNAL(readyRead()), this, SLOT(ReadData()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(Disconnecting()));

    return;
}

void Peerin::ReadData()
{

    return;
}
