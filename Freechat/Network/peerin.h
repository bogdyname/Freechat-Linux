/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef PEERIN_H
#define PEERIN_H

#include "Network/connectionf2f.h"

class Peerin : public ConnectionF2F
{
    Q_OBJECT

    Peerin();
    ~Peerin();

private:
    void MakeSocket();
    void SocketError();
    void SocketConnected();
    void SocketDisconnected();

signals:
    void ShowWANIpForUser();

public slots:
    void PassOnMyIpAddress();

private:
    QTcpSocket *socket = nullptr;
    QString strPassOnWANip;
};
#endif
