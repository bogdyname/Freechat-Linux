/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef BIN_H
#define BIN_H

#include <QString>
#include <QList>

class Bin : public QObject
{
    Q_OBJECT

private:
    QList<QString> listWithNickName;
    QList<QString> listWithIpAddress;

public:
    ~Bin();
    Bin(QObject *parent = nullptr);

private:
    void WriteInNickNameListOfPeers(const QString &nickname);
    void WriteInIpListOfPeers(const QString &ip);

    void RemoveFromIpLIst();
    void RemoveFromNickNameList();

    void GetElementFromIpList();
    void GetElementFromNickNameList();
};
#endif
