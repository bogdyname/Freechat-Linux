/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef PEERIN_H
#define PEERIN_H

#include "Bin/freechat.h"
#include <QTcpServer>
#include <QTcpSocket>

class Freechat;
class QTcpSocket;
class QTcpServer;

class Peerin : public QTcpServer
{
    Q_OBJECT

private:
    QTcpServer *server = nullptr;
    quint16 nextBlockSize;
    QTcpSocket *clientSocket1 = nullptr;
    QTcpSocket *clientSocket2 = nullptr;

public:
    explicit Peerin(QObject *parent = nullptr);
    ~Peerin();

private:
    void SendResponseToClient(QTcpSocket *socket, QString &messages);

public slots:
    virtual void SlotNewConnection();
    void SendToClientFlush();
    void SlotReadClient ();

};
#endif
