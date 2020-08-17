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

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server();
    ~Server();

private:
    QTcpServer *server = nullptr;
    QTcpSocket *socket = nullptr;
};

#endif
