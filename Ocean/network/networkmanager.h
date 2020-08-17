/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
***Created by bogdyname
*/

#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QNetworkInterface>
#include <QNetworkReply>
#include <QHostAddress>
#include <QtNetwork>
#include <QObject>

class NetworkManager : public QObject
{
    Q_OBJECT

public:
    NetworkManager();
    ~NetworkManager();

signals:
    void SendStatusOfNetwork(bool status);

public slots:
    void CallSynchronizationApp();
    void CallSynchronizationPlayList(const QString &playlist);
    void CallSynchronizationTrack(const QString &track);

private:
    bool CheckStatusOfNetwork();

};

#endif
