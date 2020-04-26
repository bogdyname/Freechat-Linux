#include "network.h"

Network::Network()
{
    Network::networkManager = new QNetworkAccessManager();
    QUrl url = QString("http://www.cbr.ru/scripts/XML_daily.asp");
    Network::networkManager->get(QNetworkRequest(url));

    QObject::connect(Network::networkManager, SIGNAL(encrypted(QNetworkReply *)), this, SLOT(GetXMLFile(QNetworkReply *)));

    return;
}

Network::~Network()
{

}

void Network::GetXMLFile(QNetworkReply *reply)
{
    if(!reply->error())
    {

    }
    else
    {
        qDebug() << "Error reply";
    }

    return;
}

void Network::ParsingXMLFile()
{

    return;
}
