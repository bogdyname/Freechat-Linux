/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include <QtNetwork>
#include "userclient.h"
#include "connection.h"
#include "peermanager.h"

PeerManager::PeerManager(UserClient *userclient)
    : QObject(userclient)
{
    this->userclient = userclient;

    static const char *envVariables[] =
    {
        "USERNAME", "USER", "USERDOMAIN",
        "HOSTNAME", "DOMAINNAME"
    };

    for (const char *varname : envVariables)
    {
        username = qEnvironmentVariable(varname);
        if (!username.isNull())
        {
            break;
        }
        else
        {
            /*CLEAR CODE*/
        }
    }

    if (username.isEmpty())
    {
        username = "unknown";
    }
    else
    {
        /*CLEAR CODE*/
    }
    UpdateAddresses();
    serverPort = 0;

    broadcastSocket.bind(QHostAddress::Any, broadcastPort,
    QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);

    connect(&broadcastSocket, SIGNAL(readyRead()),
            this, SLOT(ReadBroadcastDatagram()));

    broadcastTimer.setInterval(BroadcastInterval);
    connect(&broadcastTimer, SIGNAL(timeout()),
            this, SLOT(SendBroadcastDatagram()));
}

void PeerManager::SetServerPort(int port)
{
    serverPort = port;
}

QString PeerManager::UserName() const
{
    return username;
}

void PeerManager::StartBroadcasting()
{
    broadcastTimer.start();
}

bool PeerManager::IsWLANHostAddress(const QHostAddress &address)
{
    foreach (QHostAddress localAddress, ipAddresses)
    {
        if (address.isEqual(localAddress))
        {
            return true;

        }
        else
        {
            /*CLEAR CODE*/
        }
    }
    return false;
}

void PeerManager::SendBroadcastDatagram()
{
    QByteArray datagram;
    {
        QCborStreamWriter writer(&datagram);
        writer.startArray(2);
        writer.append(username);
        writer.append(serverPort);
        writer.endArray();
    }

    bool validBroadcastAddresses = true;
    foreach (QHostAddress address, broadcastAddresses)
    {
        if (broadcastSocket.writeDatagram(datagram,
                     address, broadcastPort) == -1)
        {
            validBroadcastAddresses = false;
        }
        else
        {
            /*CLEAR CODE*/
        }
    }

    if (!validBroadcastAddresses)
    {
        UpdateAddresses();
    }
    else
    {
        /*CLEAR CODE*/
    }
}

void PeerManager::ReadBroadcastDatagram()
{
    while (broadcastSocket.hasPendingDatagrams())
    {
        QHostAddress senderIp;
        quint16 senderPort;
        QByteArray datagram;
        datagram.resize(broadcastSocket.pendingDatagramSize());
        if (broadcastSocket.readDatagram(datagram.data(),
           datagram.size(), &senderIp, &senderPort) == -1)
        {
            continue;
        }
        else
        {
            /*CLEAR CODE*/
        }

        int senderServerPort;
        {
            QCborStreamReader reader(datagram);
            if (reader.lastError() != QCborError::NoError || !reader.isArray())
            {
                continue;
            }
            else
            {
                /*CLEAR CODE*/
            }
            if (!reader.isLengthKnown() || reader.length() != 2)
            {
                continue;
            }
            else
            {
                /*CLEAR CODE*/
            }

            reader.enterContainer();

            if (reader.lastError() != QCborError::NoError || !reader.isString())
            {
                continue;
            }
            else
            {
                /*CLEAR CODE*/
            }
            while (reader.readString().status == QCborStreamReader::Ok)
            {

            }

            if (reader.lastError() != QCborError::NoError || !reader.isUnsignedInteger())
            {
                continue;
            }
            else
            {
                /*CLEAR CODE*/
            }
            senderServerPort = reader.toInteger();
        }

        if (IsWLANHostAddress(senderIp) && senderServerPort == serverPort)
        {
            continue;
        }
        else
        {
            /*CLEAR CODE*/
        }
        if (!userclient->HasConnection(senderIp))
        {
            Connection *connection = new Connection(this);
            emit NewConnection(connection);
            connection->connectToHost(senderIp, senderServerPort);
        }
        else
        {
            /*CLEAR CODE*/
        }
    }
}

void PeerManager::UpdateAddresses()
{
    broadcastAddresses.clear();
    ipAddresses.clear();
    foreach (QNetworkInterface interface, QNetworkInterface::allInterfaces())
    {
        foreach (QNetworkAddressEntry entry, interface.addressEntries())
        {
            QHostAddress broadcastAddress = entry.broadcast();
            if (broadcastAddress != QHostAddress::Null && entry.ip() != QHostAddress::LocalHost)
            {
                broadcastAddresses << broadcastAddress;
                ipAddresses << entry.ip();
            }
            else
            {
                /*CLEAR CODE*/
            }
        }
    }
}
