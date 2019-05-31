/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "username.h"
#include "datasave.h"
#include "freechat.h"
#include "connectionf2f.h"
#include "usernametable.h"

Usernametable::Usernametable(QObject *parent)
    : QFile(parent)
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

    name.setFileName("name.txt");
    macAddres.setFileName("macad.txt");
}

QString Usernametable::GetIpV4AndV6Protocol()
    {
        if((list[nIter].protocol() == QAbstractSocket::IPv4Protocol) &&
                (list[nIter].protocol() == QAbstractSocket::IPv6Protocol))
        {
            qDebug() << list[nIter].toString() << endl;
        }
        else
        {
            /*clear code*/
        }

        return list[nIter].toString();
}

void Usernametable::GetIpAddress()
{
    for(nInter < list.count();; nInter++)
    {
        if(!list[nInter].isLoopback())
        {
            GetIpV4AndV6Protocol();
        }
        else
        {
            /*clear code*/
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

bool Usernametable::CheckForMACFileExists()
{
    if(exists("macad.txt"))
    {
        return true;
    }
    else
    {
         /*clear code*/
    }
}

bool Usernametable::CheckForMACFileIsOpen()
{
    if(macAddres.isOpen())
    {
        return true;
    }
    else
    {
         /*clear code*/
    }
}

void Usernametable::SaveUsersMACAddresses()
{
    ((CheckForMACFileExists() == true) && (CheckForMACFileIsOpen() == true)) ?
     (macAddres.open(WriteOnly)), macAddres.write(textWithMacAddresOfUser.toUtf8()) :
      macAddres.flush();

      macAddres.close();

    return;
}
