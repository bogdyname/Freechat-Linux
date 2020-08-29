/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
***Created by bogdyname
*/

#include "server.h"

Server::Server(QObject *parent)
    : QTcpServer(parent)
{
    try
    {
        server = new QTcpServer(this);
    }
    catch(std::bad_alloc &exp)
    {
        qCritical() << "Exception caught: " << exp.std::bad_alloc::what();
        exit(1);
    }
    catch(...)
    {
        qCritical() << "Some exception caught";
        exit(1);
    }

    if (server->listen(QHostAddress::Any, 6666))
        qDebug() << "Server started!";
    else
    {
        qCritical() << "Server not started: " << QTcpServer::errorString();

        server->QTcpServer::close();
    }

    //setting up server
    server->setMaxPendingConnections(1);

    return;
}

Server::~Server()
{
    qDebug() << "Destructor from server.cpp";

    return;
}
