#ifndef NETWORK_H
#define NETWORK_H

#include <QUrl>
#include <QDebug>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class Network : public QNetworkAccessManager
{
    Q_OBJECT

public:
    Network();
    ~Network();

private slots:
    void GetXMLFile(QNetworkReply *reply);
    void ParsingXMLFile();

private:
    QNetworkAccessManager *networkManager = nullptr;
};

#endif
