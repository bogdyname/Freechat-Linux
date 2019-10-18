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
    //signals from freechat for connect UI with bin header

    /*
    connect(, SIGNAL(), this, SLOT(AddPeer(QString)));
    connect(, SIGNAL(), this, SLOT(DeletePeer()));
    connect(, SIGNAL(), this, SLOT(GetNickname()));
    */
}

Bin::~Bin()
{

}

void Bin::AddPeer(QString &nickname, QString &Lanip, QString &Wanip)
{
    WriteElementsInList(listWithNickName, nickname);
    WriteElementsInList(listWithWANIpAddress, Lanip);
    WriteElementsInList(listWithLANIpAddress, Wanip);

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
