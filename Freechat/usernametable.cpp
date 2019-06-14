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

          QString macOfUser;
          GetMacAddresses(macOfUser);

          QString fname = "macadd" +
                  QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss") + ".txt";
          QFile file(fname);

          if((file.exists()) && (file.isOpen()))
          {
               if(file.open(WriteOnly))
               {
                   QTextStream writeStream(&file);
                   writeStream << macOfUser;
                   file.flush();
               }
               else
               {
                   file.close();
               }
          }
}

inline QString Usernametable::GetIpV4AndV6Protocol()
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

inline void Usernametable::GetIpAddresses()
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

    return;
}

inline void Usernametable::GetMacAddresses(QString textWithMacAddresOfUser)
{
            foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
            {
                textWithMacAddresOfUser += interface.hardwareAddress();
            }

    return;
}

void Usernametable::TranslationName(QFile &fileWithMAC, QString &translator)
{


    return;
}
