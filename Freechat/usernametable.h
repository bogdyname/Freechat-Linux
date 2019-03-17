/*
***Copyright (C) 2019 Freechat Inc
***Contact: bogdyname@gmail.com
*/

#ifndef USERNAMETABLE_H
#define USERNAMETABLE_H

#include <QtNetwork/QNetworkInterface>
#include <QtCore/QCoreApplication>
#include <QAbstractSocket>
#include <QHostAddress>
#include <QSettings>
#include <QHostInfo>
#include <QString>
#include <QList>


class usernametable : public QString
{
    Q_OBJECT

protected:
    QString getMacAddress()
    {
        QString text;
        foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
        {
            text += interface.hardwareAddress(); //CHECK THIS OUT
        }
        return text;
    }

protected:
    ~usernametable();

protected:
    QList<QHostAddress> list = QNetworkInterface::allAddresses();

    for(int nInter = 0; nInter < list.count(); nInter++)
    {
    if(!list[nInter].isLoopback())
           if(list[nIter].protocol() == QAbstractSocket::IPv4Protocolo)
               qDebug() << list[nIter].toString();
    }
};

class tabletranslation
{
    QString translationName()
    {
        QString name;


    }
};

#endif // USERNAMETABLE_H
