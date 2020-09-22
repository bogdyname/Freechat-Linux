/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
***Created by bogdyname
*/

#include "networkmanager.h"

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent)
{

    return;
}

NetworkManager::~NetworkManager()
{
    qDebug() << "Destructor from networkmanager.cpp";
}

void NetworkManager::CallSynchronizationApp()
{

    return;
}

void NetworkManager::CallSynchronizationPlayList(const QString &playlist)
{
    if(playlist == "")
        return;

    return;
}

void NetworkManager::CallSynchronizationTrack(const QString &track)
{
    if(track == "")
        return;

    return;
}

bool NetworkManager::CheckStatusOfNetwork()
{
    QEventLoop loop;
    QNetworkAccessManager nam;
    QNetworkRequest req(QUrl("http://www.google.com"));
    QNetworkReply *reply = nam.get(req);
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if(reply->bytesAvailable())
    {
        emit this->SendStatusOfNetwork(true);
        return true;
    }
    else
    {
        emit this->SendStatusOfNetwork(false);
        return false;
    }
}
