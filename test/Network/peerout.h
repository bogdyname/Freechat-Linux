/*
***Copyright (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef PEEROUT
#define PEEROUT

#include "Bin/freechat.h"
#include <QTcpSocket>

class Freechat;
class QTcpSocket;
class ConnectionF2F;

class Peerout : public QTcpSocket
{
    Q_OBJECT

public:
    explicit Peerout();
    ~Peerout();

public:
    void SlotConnecting();

public slots:
    void SlotReadyRead();
    void SlotConnected();
    void SlotSendToServer();
    void SlotError(QAbstractSocket::SocketError);

private:
    QTcpSocket *socket = nullptr;
    quint16 nextBlockSize;
};
#endif
