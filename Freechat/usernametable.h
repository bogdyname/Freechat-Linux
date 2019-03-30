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
#include <QSettings>
#include <QHostInfo>
#include <QString>
#include <QList>

class Freechat;
class Connection;

class Usernametable : public QObject
{
    Q_OBJECT

public:
    Usernametable(QObject *parent = nullptr);
    ~Usernametable();

    QString GetIpV4Protocol();
    QString GetIpAddress();
    QString GetMacAddress();
    QString TranslationName();
    QString OutputOnDisplay();


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
