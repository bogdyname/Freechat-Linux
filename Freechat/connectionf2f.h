/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include <QNetworkInterface>
#include <QAbstractSocket>
#include <QNetworkSession>
#include <QHostAddress>
#include <QHostAddress>
#include <QTimerEvent>
#include <QTcpSocket>
#include <QHostInfo>
#include <QtNetwork>
#include <QSsl>

using namespace QSsl;
using namespace QPasswordDigestor;

#ifndef CONNECTIONF2F_H
#define CONNECTIONF2F_H

class ConnectionF2F : public QTcpSocket
{
    Q_OBJECT

    ConnectionF2F(QObject *parent = nullptr);
    ~ConnectionF2F();

private slots:
    void DigitalSignature();
    void ConnectingToPeer();
    void SocketConnected();
    void SocketDisconnected();
    void ReadyReadOfData();

private:
    quint16 GetPeerPort();
    QHostAddress GetPeerAddress();

private:
    QTimerEvent TimerForWaitingConnection();

};

#endif // CONNECTIONF2F_H

#ifndef CLIENT_H
#define CLIENT_H

class Client : public QTcpSocket
{
    Q_OBJECT

public:
    Client(QObject *parent = nullptr);
    ~Client();

    void GetSocketFromClient();

private:
    void MakeSocketClient();
    void SockedErroe();

public:
    quint16 GetPeerPort();
    QHostAddress GetPeerAddress();

private:
    quint16 PeerPort();
    QHostAddress PeerAddress();
};

#endif // CLIENT_H

#ifndef HOST_H
#define HOST_H

class Host : public QTcpServer
{
    Q_OBJECT

public:
    Host(QObject *parent = nullptr);
    ~Host();

    void GetSocketFromHost();

private:
    void MakeSocketHost();
    void SockedErroe();
    void ListenPort();
};

#endif // HOST_H
