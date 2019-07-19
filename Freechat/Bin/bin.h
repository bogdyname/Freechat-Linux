/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef BIN_H
#define BIN_H

#include <QHostAddress>
#include <QJsonObject>
#include <QIODevice>
#include <QHostInfo>
#include <QSaveFile>
#include <QDateTime>
#include <QString>
#include <QFile>

class Bin : public QObject
{
    Q_OBJECT

public:
    ~Bin();
    Bin(QObject *parent = nullptr);

private:
    void ListWithNickNameOfPeers(const QString &nickname);
    void ListWithIpOfPeers(const QString &ip);

    void InsertInIpList();
    void InsertInNicknNameList();

    void RemoveFromIpLIst();
    void RemoveFromNickNameList();

    void SortNickNameList();
    void SortIpList();
};
#endif
