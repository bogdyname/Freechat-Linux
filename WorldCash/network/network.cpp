#include "network.h"

Network::Network()
{
    Network::networkManager = new QNetworkAccessManager();
    QUrl url = QString("");

    QObject::connect(Network::networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(GetXMLFile(QNetworkReply *)));

    Network::networkManager->QNetworkAccessManager::get(QNetworkRequest(url));

    return;
}

Network::~Network()
{

}

void Network::GetXMLFile(QNetworkReply *reply)
{
    if(!reply->QNetworkReply::error())
    {

    }

    return;
}

void Network::ParsingXMLFile()
{

    return;
}
