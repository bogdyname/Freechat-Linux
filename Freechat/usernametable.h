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
            text += interface.hardwareAddress();
        }
        return text;
    }

protected:
    ~usernametable();

protected:
    QList<QHostAddress> list = QNetworkInterface::allAddresses();

    QString getIpAddress()
    {
        for(int nInter = 0; nInter < list.count(); nInter++)
        {
            if(!list[nInter].isLoopback())
            {
                getIpV4Protocol();
            }
            else
            {
             /*CLEAR CODE*/
            }
        }
    }

    QString getIpV4Protocol()
    {
        int nIter = 0;

        if(list[nIter].protocol() == QAbstractSocket::IPv4Protocol)
        {
           qDebug() << list[nIter].toString();
        }
        else
        {
         /*CLEAR CODE*/
        }

    }
};

class tableTranslation
{
private:
    QString translationName()
    {
        QString name;

        /*
        CODE
        WILL
        BE
        HERE
        */
    }
};

#endif // USERNAMETABLE_H
