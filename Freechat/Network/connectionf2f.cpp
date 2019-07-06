/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Network/connectionf2f.h"
#include "Bin/freechat.h"
#include "Bin/bin.h"

ConnectionF2F::ConnectionF2F(QObject *parent)
    : QTcpSocket(parent)
{
    Peerout connecting;
}

void ConnectionF2F::PassOnWANIp(QString &buffer)
{
    GetIpAddressFromWAN(buffer);

    return;
}

void ConnectionF2F::GetIpAddressFromWAN(QString &textWithIPAddres)
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
        });

        textWithIPAddres = IP.toString();

        return;
}
