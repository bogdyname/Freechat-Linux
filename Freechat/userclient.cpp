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
    peerManager->SetServerPort(userserver.serverPort());
    peerManager->StartBroadcasting();

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
        connection->SendMessage(message);
}

QString UserClient::NickName() const
{
    return peerManager->UserName() + '@' + QHostInfo::localHostName()
           + ':' + QString::number(userserver.serverPort());
}
