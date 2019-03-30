/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include <QtNetwork>
#include "userserver.h"
#include "connection.h"

UserServer::UserServer(QObject *parent)
    : QTcpServer(parent)
{
    listen(QHostAddress::Any);
}

void UserServer::InComingConnection(qintptr socketDescription)
{
    Connection *connection = new Connection(socketDescription, this);
    emit NewConnection(connection);
}
