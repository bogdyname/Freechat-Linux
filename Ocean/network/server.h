/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
***Created by bogdyname
*/

#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>

class Server : public QTcpServer
{
    Q_OBJECT
    Q_CLASSINFO("Version", "0.5")

public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

    /*
        1) Read client data
        2) Send response to client about receiving
    */

private slots:
    void Receiver();
    void Sender();

private:
    qint64 nextBlockSize;
    QTcpServer *server = nullptr;
    QTcpSocket *socket = nullptr;
};

#endif
