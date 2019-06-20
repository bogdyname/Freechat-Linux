/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "username.h"
#include "datasave.h"
#include "freechat.h"
#include "ui_freechat.h"
#include "connectionf2f.h"

Username::Username(QObject *parent)
    : QFile(parent)
{

}

inline void Username::ReadingIpAddress(QFile &fileWithIP)
{
    if ((fileWithIP.exists()) && (fileWithIP.open(ReadOnly)))
    {
        ui->listViewWithNetworkData->setText(fileWithIP.readAll());
        fileWithIP.close();
    }
    else
    {
        /*clear code*/
    }

    return;
}

inline void Username::ReadingMACAddress(QFile &fileWithMac)
{
    if ((fileWithMac.exists()) && (fileWithMac.open(ReadOnly)))
    {
        ui->listViewWithNetworkData->setText(fileWithMac.readAll());
        fileWithMac.close();
    }
    else
    {
        /*clear code*/
    }

    return;
}

void Username::TranslationName(QFile &fileWithMAC, QString &translator)
{
    fileWithMAC = ReadingMACAddress(fileWithMAC);

    return;
}


Usernametable::Usernametable(QObject *parent)
    : QFile(parent)
{
          QString macOfUser;
          GetMacAddress(macOfUser);

          QString fnamem = "macadd" +
                  QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss") + ".txt";
          QFile filem(fnamem);

          if((filem.exists()) && (filem.isOpen()))
          {
               if(filem.open(WriteOnly))
               {
                   QTextStream writeStream(&filem);
                   writeStream << macOfUser;
                   filem.flush();
               }
               else
               {
                   filem.close();
               }
          }

          QString ipOfUser;
          GetIpAddressFromWAN(ipOfUser);

          QString fname = "ipadd" +
                  QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss") + ".txt";
          QFile file(fname);

          if((file.exists()) && (file.isOpen()))
          {
               if(file.open(WriteOnly))
               {
                   QTextStream writeStream(&file);
                   writeStream << ipOfUser;
                   file.flush();
               }
               else
               {
                   file.close();
               }
          }
}

inline void Usernametable::GetMacAddress(QString &textWithMacAddresOfUser)
{
            foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
            {
                textWithMacAddresOfUser += interface.hardwareAddress();
            }

    return;
}

void Usernametable::GetIpAddressFromWAN(QString &textWithIPAddres)
{
        QNetworkAccessManager networkManager;
        QHostAddress IP;

        QUrl url("https://api.ipify.org");
        QUrlQuery query;
        query.addQueryItem("format", "json");
        url.setQuery(query);

        QNetworkReply* reply = networkManager.get(QNetworkRequest(url));

        connect(reply, &QNetworkReply::finished, [&]()
        {
            if(reply->error() != QNetworkReply::NoError)
            {
                qDebug() << "error: " << reply->error();
            }
            else
            {
                QJsonObject jsonObject= QJsonDocument::fromJson(reply->readAll()).object();
                QHostAddress ip(jsonObject["ip"].toString());

                IP = ip;
            }
            reply->deleteLater();
        }
        );

        textWithIPAddres = IP.toString();

        return;
}
