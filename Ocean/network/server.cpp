/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
***Created by bogdyname
*/

#include "server.h"

Server::Server()
{
    try
    {
        server = new QTcpServer(this);
    }
    catch(std::bad_alloc &exp)
    {
        qCritical() << "Exception caught: " << exp.std::bad_alloc::what();
        abort();
    }
    catch(...)
    {
        qCritical() << "Some exception caught";
        abort();
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

}
