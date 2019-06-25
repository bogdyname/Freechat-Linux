/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "ui_username.h"
#include <QtNetwork/QNetworkInterface>
#include <QtCore/QCoreApplication>
#include <QAbstractSocket>
#include <QHostAddress>
#include <QJsonObject>
#include <QTextStream>
#include <QDataStream>
#include <QByteArray>
#include <QIODevice>
#include <QHostInfo>
#include <QSaveFile>
#include <QDateTime>
#include <QString>
#include <QFile>

#ifndef USERNAME_H
#define USERNAME_H

class Username : public QFile, private Ui::Username
{
    Q_OBJECT

public:
    ~Username();
    Username(QWidget *parent = nullptr);

public slots:
    inline void ReadingIpAddress(QFile &fileWithIP);
    inline void ReadingMACAddress(QFile &fileWithMac);
    virtual void TranslationName(QFile &fileWithMAC, QString &translator);
};
#endif

#ifndef USERNAMETABLE_H
#define USERNAMETABLE_H
class Username;

class Usernametable : public Username
{
    Q_OBJECT

public:
    ~Usernametable() override;
    Usernametable(QWidget *parent = nullptr);

private:
    QString *buffer = nullptr;
    const QString username;

public slots:
    void TranslationName(QFile &fileWithMAC, QString &translator) override;

protected:
    inline void MakeFileWithIp();
    inline void MakeFileWithMac();
    void GetIpAddressFromWAN(QString &textWithIPAddres);
    inline void GetMacAddress(QString &textWithMacAddresOfUser);
};
#endif
