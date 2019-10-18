/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef BIN_H
#define BIN_H

#include <QList>
#include <QString>
#include <iostream>
#include <algorithm>

class Bin : public QObject
{
    Q_OBJECT

private:
    QList<QString> listWithNickName;
    QList<QString> listWithWANIpAddress;
    QList<QString> listWithLANIpAddress;

public:
    ~Bin();
    explicit Bin(QObject *parent = nullptr);

private:
    void AddPeer(QString &nickname, QString &Lanip, QString &Wanip);
    void DeletePeer();
    void GetNickname(QList<QString> &nick);

private:
    template <typename Wcontainer>
    Wcontainer WriteElementsInList(Wcontainer &list, const QString &element);

    template <typename Gcontainer>
    Gcontainer GetElementsFromList(Gcontainer &list);

    template <typename Rcontainer>
    Rcontainer RemoveElementsFromList(Rcontainer &list);
};
#endif
