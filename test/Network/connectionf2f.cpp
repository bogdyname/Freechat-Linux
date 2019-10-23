/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Network/connectionf2f.h"

extern QString yourIp;

ConnectionF2F::ConnectionF2F(QObject *parent)
    : QTcpSocket(parent)
{
     /*now is empty*/

    return;
}

ConnectionF2F::~ConnectionF2F()
{

    return;
}

int ConnectionF2F::CheckConnection()
{
    QNetworkAccessManager nam;
    QNetworkRequest req(QUrl("http://www.google.com"));
    QNetworkReply *reply = nam.get(req);
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if(reply->bytesAvailable())
    {
        return 101;
    }
    else
    {
        return 404;
    }
}

void ConnectionF2F::NetworkInfo()
{
       QString localhostname =  QHostInfo::localHostName();
       QString localhostIP;
       QList<QHostAddress> hostList = QHostInfo::fromName(localhostname).addresses();

       foreach (const QHostAddress& address, hostList)
       {
           if (address.protocol() == QAbstractSocket::IPv4Protocol && address.isLoopback() == false)
           {
                localhostIP = address.toString();
           }
           else
           {
               /*clear code*/
           }
       }

       QString localMacAddress;
       QString localNetmask;

       foreach (const QNetworkInterface& networkInterface, QNetworkInterface::allInterfaces())
       {
           foreach (const QNetworkAddressEntry& entry, networkInterface.addressEntries())
           {
               if (entry.ip().toString() == localhostIP)
               {
                   localMacAddress = networkInterface.hardwareAddress();
                   localNetmask = entry.netmask().toString();
                   break;
               }
               else
               {
                   /*clear code*/
               }
           }
       }

       #ifndef Q_DEBUG
       qDebug() << "Localhost name: " << localhostname;
       qDebug() << "IP = " << localhostIP;
       qDebug() << "MAC = " << localMacAddress;
       qDebug() << "Netmask = " << localNetmask;
       #endif

       Freechat::yourIp += localhostIP;
}
