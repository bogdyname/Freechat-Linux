/*
***Copyright (C) 2019 Freechat Inc
***Contact: bogdyname@gmail.com
*/

#ifndef USERNAMETABLE_H
#define USERNAMETABLE_H

#include <QtCore/QCoreApplication>
#include <QtNetwork/QNetworkInterface>
#include <QString>

class usernametable
{
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
    usernametable();
};

#endif // USERNAMETABLE_H
