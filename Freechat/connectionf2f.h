/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef CONNECTIONF2F_H
#define CONNECTIONF2F_H

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

class ConnectionF2F : public QTcpSocket
{
    Q_OBJECT

    ConnectionF2F(QObject *parent = nullptr);

private slots:
    void DigitalSignature();
    void ConnectingToPeer();
    void SocketConnected();
    void SocketDisconnected();
    void ReadyForReadOfData();

public:
    void SockedErroe();
    void MakeSocket();

protected:
    quint16 GetPeerPort();
    QHostAddress GetPeerAddress();

private:
    QTimerEvent TimerForWaitingConnection();

};

#endif // CONNECTIONF2F_H
