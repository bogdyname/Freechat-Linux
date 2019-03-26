/*
***Copyright (C) 2019 Softwater Inc
***Contact: bogdyname@gmail.com
*/

#include <QtNetwork>
#include "userclient.h"
#include "connection.h"
#include "peermanager.h"

UserClient::UserClient()
{
    peerManager = new PeerManager(this);
    peerManager->setServerPort(server.serverPort());
    peerManager->startBroadcasting();

    QObject::connect(peerManager, SIGNAL(newConnection(Connection*)),
                     this, SLOT(newConnection(Connection*)));
    QObject::connect(&server, SIGNAL(newConnection(Connection*)),
                     this, SLOT(newConnection(Connection*)));
}

void UserClient::sendMessage(const QString &message)
{
    if (message.isEmpty())
    {
        return;
    }
    else
    {
        /*CLEAR CODE*/
    }

    QList<Connection *> connections = peers.values();
    foreach (Connection *connection, connections)
        connection->sendMessage(message);
}

QString UserClient::nickName() const
{
    return peerManager->userName() + '@' + QHostInfo::localHostName()
           + ':' + QString::number(server.serverPort());
}
