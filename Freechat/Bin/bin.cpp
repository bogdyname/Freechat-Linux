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

void Bin::WriteInNickNameListOfPeers(const QString &nickname)
{
    listWithNickName << nickname;

    return;
}

void Bin::WriteInIpListOfPeers(const QString &ip)
{
    listWithIpAddress << ip;

    return;
}

void Bin::GetElementFromIpList()
{
    QList<QString>::const_iterator it = listWithIpAddress.constBegin();

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
    QList<QString>::const_iterator it = listWithNickName.constBegin();

    for(; it != listWithNickName.end(); ++it)
    {
        #ifndef Q_DEBUG
        qDebug() << "Element from Nickname list: " << *it << endl;
        #endif
    }

    return;
}

void Bin::RemoveFromIpLIst()
{
    QList<QString>::iterator it = listWithIpAddress.begin();

    for(; it != listWithIpAddress.end(); ++it)
    {
        #ifndef Q_DEBUG
        qDebug() << "Deleted element from Nickname list: " << *it << endl;
        #endif

        //listWithIpAddress.erase(*it);
    }

    return;
}

void Bin::RemoveFromNickNameList()
{
    QList<QString>::iterator it = listWithNickName.begin();

    for(; it != listWithNickName.end(); ++it)
    {
        #ifndef Q_DEBUG
        qDebug() << "Deleted element from Nickname list: " << *it << endl;
        #endif

        //listWithNickName.erase(*it);
    }

    return;
}
