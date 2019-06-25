/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "User/username.h"
#include "Data/datasave.h"
#include "User/freechat.h"
#include "ui_freechat.h"
#include "Network/connectionf2f.h"

Username::Username(QWidget *parent)
    : QFile(parent)
{
    //HEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHERE
    //HEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHERE
    //HEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHERE
}

Username::~Username()
{
    //HEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHERE
    //HEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHERE
    //HEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHERE
}

inline void Username::ReadingIpAddress(QFile &fileWithIP)
{
    if ((fileWithIP.exists()) && (fileWithIP.open(ReadOnly)))
    {
        fileWithIP.readAll();
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
        fileWithMac.readAll();
        fileWithMac.close();
    }
    else
    {
        /*clear code*/
    }

    return;
}

Usernametable::Usernametable(QWidget *parent)
    : Username(parent)
{
     MakeFileWithIp();
     MakeFileWithMac();

     //HEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHERE
     //HEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHERE
     //HEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHERE
}

Usernametable::~Usernametable()
{
    delete buffer;
}

void Usernametable::TranslationName(QFile &fileWithMAC, QString &translator)
{
    QString *buffer = new QString;
    GetMacAddress(translator);

    QWidget *widget = new QWidget;
    Ui::Username ui;
    ui.setupUi(widget);

    if((fileWithMAC.exists()) && (fileWithMAC.open(ReadOnly)))
    {
        fileWithMAC.readAll();
        buffer << fileWithMAC;
        fileWithMAC.close();
    }
    else
    {
        fileWithMAC.flush();
    }

    //HEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHERE
    //HEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHERE
    //HEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHEREHERE

    return;
}

inline void Usernametable::MakeFileWithIp()
{
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

inline void Usernametable::MakeFileWithMac()
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
