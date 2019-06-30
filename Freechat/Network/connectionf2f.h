/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Bin/bin.h"
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

public:
    ConnectionF2F(QObject *parent = nullptr);
    ~ConnectionF2F();

    void ConnectingToPeer();
    void ReadyReadOfData();

    void AskForConnectingToPortPeer();
    void AskForDisconnectingFromPortPeer();
};
#endif

#ifndef PEEROUT
#define PEEROUT
class Peerout : public ConnectionF2F
{
    Q_OBJECT

public:
    Peerout();
    ~Peerout();

private:
    void MakeSocket();
    void SocketError();
    void SocketConnected();
    void SocketDisconnected();
    void GetIpAddressFromWAN(QString &textWithIPAddres);

private:
    QTcpSocket *socket = nullptr;
    QString strWANip;
};
#endif

#ifndef PEERONSIDE
#define PEERONSIDE
class Peerinside : public ConnectionF2F
{
    Q_OBJECT

    Peerinside();
    ~Peerinside();

private:
    void MakeSocket();
    void SocketError();
    void SocketConnected();
    void SocketDisconnected();

private:
    QTcpSocket *socket = nullptr;
};
#endif
