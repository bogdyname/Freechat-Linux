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
#include <QTextStream>
#include <QByteArray>
#include <QIODevice>
#include <QHostInfo>
#include <QSaveFile>
#include <QDateTime>
#include <QString>
#include <QFile>

class Username;

class Usernametable : public QFile
{
    Q_OBJECT

public:
    Usernametable(QObject *parent = nullptr);

    void GetIpAddresses();
    void GetMacAddresses(QString textWithMacAddresOfUser);
    QString GetIpV4AndV6Protocol();

public:
    void TranslationName(QFile &fileWithMAC, QString &translator);

protected:
    bool CheckForMACFileExists(QFile &fileWithMAC);
    bool CheckForMACFileIsOpen(QFile &fileWithMAC);

public:
    int nIter = 0;
    int nInter = 0;
    QString protocol = "???";
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    QList<QHostAddress> addresses = QHostInfo::fromName(QHostInfo::localHostName()).addresses();
};


#endif // USERNAMETABLE_H
