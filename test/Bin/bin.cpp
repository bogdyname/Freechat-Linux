/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Bin/bin.h"
#include "Bin/freechat.h"
#include "Network/connectionf2f.h"

using namespace std;

Bin::Bin(QObject *parent)
    : QObject(parent)
{

}

Bin::~Bin()
{

}

void Bin::Test()
{
    QList<QString>::const_iterator it = listWithNickName.constBegin();

    for(; it != listWithNickName.end(); ++it)
    {
        #ifndef Q_DEBUG
        qDebug() << "Element from list: " << *it << endl;
        #endif
    }

    return;
}

void Bin::AddPeerLan()
{
    WriteElementsInList(listWithWANIpAddress, Freechat::lanIpOfPeer);

    return;
}

void Bin::AddPeerWan()
{
    WriteElementsInList(listWithLANIpAddress, Freechat::wanIpOfPeer);

    return;
}

void Bin::AddPeerNick()
{
    WriteElementsInList(listWithNickName, Freechat::nickNameOfPeer);

    return;
}

void Bin::DeletePeer()
{
    RemoveElementsFromList(listWithNickName);
    RemoveElementsFromList(listWithWANIpAddress);
    RemoveElementsFromList(listWithLANIpAddress);

    return;
}

void Bin::GetNickname(QList<QString> &nick)
{
    nick = GetElementsFromList(listWithNickName);

    return;
}

template <typename Wcontainer>
Wcontainer Bin::WriteElementsInList(Wcontainer &list, const QString &element)
{
    return list << element;
}

template <typename Gcontainer>
Gcontainer Bin::GetElementsFromList(Gcontainer &list)
{
    QList<QString>::const_iterator it = list.constBegin();

    for(; it != list.end(); ++it)
    {
        #ifndef Q_DEBUG
        qDebug() << "Element from list: " << *it << endl;
        #endif
    }

    return list;
}

template <typename Rcontainer>
Rcontainer Bin::RemoveElementsFromList(Rcontainer &list)
{
    QList<QString>::iterator it = list.begin();

    for(; it != list.end(); ++it)
    {
        #ifndef Q_DEBUG
        qDebug() << "Deleted element from list: " << *it << endl;
        #endif

        list.erase(it);
    }

    return list;
}
