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
        }
        );

        textWithIPAddres = IP.toString();

        return;
}


/////////////////////////////////////////////////////

Peerout::Peerout()
{
    connect(socket, SIGNAL(Connected()), this, SLOT(Connected()));
    connect(socket, SIGNAL(DoConnect()), this, SLOT(DoConnect()));
    connect(socket, SIGNAL(ReadyRead()), this, SLOT(ReadyRead()));
    connect(socket, SIGNAL(BytesWrittenOfData(qint64)), this, SLOT(BytesWrittenOfData(qint64)));
}

Peerout::~Peerout()
{
    delete socket;
}

void Peerout::DoConnect()
{
    socket = new QTcpSocket(this);

    socket->connectToHost(strWANip, 80);

        if(socket->waitForConnected(3000))
        {
            qDebug() << "Connected!";

            socket->write("DATA OF TEXT");
            socket->waitForBytesWritten(1000);
            socket->waitForReadyRead(3000);
            qDebug() << "Reading: " << socket->bytesAvailable();

            qDebug() << socket->readAll();

            socket->close();
        }
        else
        {
            qDebug() << "Not connected!";
        }

        return;
}

void Peerout::BytesWrittenOfData(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";

    return;
}

void Peerout::Connected()
{

    return;
}

void Peerout::Disconnected()
{

    return;
}

void Peerout::ReadyRead()
{
    qDebug() << "reading...";
    qDebug() << socket->readAll();

    return;
}
/////////////////////////////////////////////////////////////////

Peerinside::Peerinside()
{
    connect(&showNetworkInfo, SIGNAL(ShowWANIpForUser()), this, SLOT(PassOnMyIpAddress()));
}

void Peerinside::PassOnMyIpAddress()
{
    PassOnWANIp(strPassOnWANip);

    QMessageBox::information(this, tr("WAN IP"),
                    tr("Do not show this IP to anyone!"), tr(strPassOnWANip));

    return;
}
