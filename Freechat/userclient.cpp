/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include <QtNetwork>
#include "userclient.h"
#include "connection.h"
#include "peermanager.h"

UserClient::UserClient()
{
    peerManager = new PeerManager(this);
    peerManager->setServerPort(userserver.serverPort());
    peerManager->startBroadcasting();

    QObject::connect(peerManager, SIGNAL(NewConnection(Connection*)),
                     this, SLOT(NewConnection(Connection*)));
    QObject::connect(&userserver, SIGNAL(NewConnection(Connection*)),
                     this, SLOT(NewConnection(Connection*)));
}

void UserClient::SendMessage(const QString &message)
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

QString UserClient::NickName() const
{
    return peerManager->userName() + '@' + QHostInfo::localHostName()
           + ':' + QString::number(userserver.serverPort());
}
