/*
***Copyright (C) 2019 Freechat Inc
***Contact: bogdyname@gmail.com
*/

#include <QtNetwork>
#include "userclient.h"
#include "connection.h"

Client::Client()
{
    peerManager = new PeerManager(this);
    peerManager->setServerPort(server.serverPort());
    peerManager->startBroadcasting();

    QObject::connect(peerManager, SIGNAL(newConnection(Connection*)),
                     this, SLOT(newConnection(Connection*)));
    QObject::connect(&server, SIGNAL(newConnection(Connection*)),
                     this, SLOT(newConnection(Connection*)));
}

void Client::sendMessage(const QString &message)
{
    if (message.isEmpty())
        return;

    QList<Connection *> connections = peers.values();
    foreach (Connection *connection, connections)
        connection->sendMessage(message);
}

QString Client::nickName() const
{
    return peerManager->userName() + '@' + QHostInfo::localHostName()
           + ':' + QString::number(server.serverPort());
}
