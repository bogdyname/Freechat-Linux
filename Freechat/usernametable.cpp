/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "username.h"
#include "datasave.h"
#include "freechat.h"
#include "connection.h"
#include "usernametable.h"

Usernametable::Usernametable(QSaveFile *parent)
    : QSaveFile(parent)
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

QString Usernametable::GetIpV4Protocol()
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

QString Usernametable::GetIpAddress()
{
    for(nInter < list.count();; nInter++)
    {
        if(!list[nInter].isLoopback())
        {
            GetIpV4Protocol();
        }
        else
        {
            /*CLEAR CODE*/
        }
    }
}

QString Usernametable::GetMacAddress()
{
            foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
            {
                textWithMacAddresOfUser += interface.hardwareAddress();
            }
    return textWithMacAddresOfUser;
}

QString Usernametable::SaveUsersMACAddress(const QString &nameOfUserMAC)
{
    qDebug() << GetMacAddress().constData() << endl;
    exit(1);
}
