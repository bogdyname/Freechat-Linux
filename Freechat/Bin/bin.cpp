/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Bin/bin.h"
#include "Data/datasave.h"
#include "Bin/freechat.h"
#include "Network/connectionf2f.h"

Bin::Bin(QObject *parent)
    : QObject(parent)
{

}

Bin::~Bin()
{

}

void Bin::ListWithNickNameOfPeers(const QString &nickname)
{
    listWithNickName << nickname;
    QList<QString>::iterator it = listWithNickName.begin();

    return;
}

void Bin::ListWithIpOfPeers(const QString &ip)
{
    listWithIpAddress << ip;
    QList<QString>::iterator it = listWithIpAddress.begin();

    return;
}

void Bin::GetElementFromIpList()
{
    QList<QString>::iterator it = listWithIpAddress.begin();

    for(; it != listWithIpAddress.end(); ++it)
    {
        #ifndef Q_DEBUG
        qDebug() << "Element from IP list: " << *it << endl;
        #endif
    }

    return;
}

void Bin::GetElementFromNickNameList()
{
    QList<QString>::iterator it = listWithNickName.begin();

    for(; it != listWithNickName.end(); ++it)
    {
        #ifndef Q_DEBUG
        qDebug() << "Element from Nickname list: " << *it << endl;
        #endif
    }

    return;
}
