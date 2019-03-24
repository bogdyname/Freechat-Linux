/*
***Copyright (C) 2019 Freechat Inc
***Contact: bogdyname@gmail.com
*/

#include "usernametable.h"
#include "username.h"
#include <iostream>

using namespace std;

Usernametable::Usernametable(QObject *parent)
    : QObject(parent)
{
          foreach (const QHostAddress & a, addresses)
          {
              switch (a.protocol())
              {
                  case QAbstractSocket::IPv4Protocol:
                      protocol = "IPv4";
                  break;
                  case QAbstractSocket::IPv6Protocol:
                      protocol = "IPv6";
                  break;
              }
              qDebug() << a.toString() << "(" << protocol << ")";
          }
}

QString Usernametable::getIpV4Protocol()
    {
        if(list[nIter].protocol() == QAbstractSocket::IPv4Protocol)
        {
            qDebug() << list[nIter].toString() << endl;
        }
        else
        {
            /*CLEAR CODE*/
        }
}

QString Usernametable::getIpAddress()
{
    for(nInter < list.count(); nInter++)
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

QString Usernametable::getMacAddress()
{
            foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
            {
                textWithMacAddresOfUser += interface.hardwareAddress();
            }
    return textWithMacAddresOfUser;
}

QString Usernametable::outputOnDisplay()
{
    qDebug() << getMacAddress().constData() << endl;
    exit(1);
}
