/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef PEERMANAGER_H
#define PEERMANAGER_H

#include <QList>
#include <QTimer>
#include <QObject>
#include <QByteArray>
#include <QUdpSocket>

class UserClient;
class Connection;

static const qint32 BroadcastInterval = 2000;
static const unsigned broadcastPort = 45000;

class PeerManager : public QObject
{
    Q_OBJECT

public:
    PeerManager(UserClient *userclient);

    QString UserName() const;
    void StartBroadcasting();
    void SetServerPort(int port);
    bool IsWLANHostAddress(const QHostAddress &address);

signals:
    void NewConnection(Connection *connection);

private slots:
    void SendBroadcastDatagram();
    void ReadBroadcastDatagram();

private:
    void UpdateAddresses();

    UserClient *userclient;

    int serverPort;
    QString username;
    QTimer broadcastTimer;
    QUdpSocket broadcastSocket;
    QList<QHostAddress> ipAddresses;
    QList<QHostAddress> broadcastAddresses;
};

#endif // PEERMANAGER_H
