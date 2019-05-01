/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef USERNAMETABLE_H
#define USERNAMETABLE_H

#include <QtNetwork/QNetworkInterface>
#include <QtCore/QCoreApplication>
#include <QAbstractSocket>
#include <QHostAddress>
#include <QByteArray>
#include <QHostInfo>
#include <QSaveFile>
#include <QString>

class Username;

class Usernametable : public QSaveFile
{
    Q_OBJECT

public:
    Usernametable(QSaveFile *parent = nullptr);
    ~Usernametable();

    QString GetIpV4Protocol();
    QString GetIpAddress();
    QString GetMacAddress();
    QString TranslationName();
    QString SaveUsersMACAddress(const QString &nameOfUserMAC);


    int nIter = 0;
    int nInter = 0;
    QString textWithMacAddresOfUser;
    QString name;
    QString macAddres;
    QString protocol = "???";
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    QList<QHostAddress> addresses = QHostInfo::fromName(QHostInfo::localHostName()).addresses();
};


#endif // USERNAMETABLE_H
