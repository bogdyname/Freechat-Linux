/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef PEERIN_H
#define PEERIN_H

#include "Network/connectionf2f.h"
#include "Network/peerout.h"

class Peerin : public QTcpServer
{
    Q_OBJECT

private:
    explicit Peerin(QObject *parent = nullptr);
    ~Peerin();

private:
    void CheckPortForConnection();
    void incomingConnection(qintptr socketDescriptor);

signals:

public slots:
    void ReadData();

private:
    QTcpServer *server = nullptr;
};
#endif
