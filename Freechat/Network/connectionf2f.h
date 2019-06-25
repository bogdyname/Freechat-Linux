/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "User/username.h"
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
class ConnectionF2F : public QTcpSocket, Usernametable
{
    Q_OBJECT

public:
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
#endif

#ifndef CLIENT_H
#define CLIENT_H
class Client : public ConnectionF2F
{
    Q_OBJECT

public:
    Client(QObject *parent = nullptr);
    ~Client();

    void GetSocketFromClient();

private:
    void MakeSocketClient();
    void SockedErroe(int socketError, const QString &message);

public:
    quint16 GetPeerPort();
    QHostAddress GetPeerAddress();

private:
    quint16 PeerPort(quint16 port);
    QHostAddress PeerAddress(const QString &hostName);

private:
    QString hostName;
    quint16 port;
    QMutex mutex;
    QWaitCondition cond;
    bool quit;
};
#endif

#ifndef HOST_H
#define HOST_H
class Host : public ConnectionF2F
{
    Q_OBJECT

public:
    Host(QObject *parent = nullptr);
    ~Host();

    void GetSocketFromHost();

private:
    void MakeSocketHost();
    void SockedErroe(int socketError, const QString &message);
    void ListenPort();
};
#endif
