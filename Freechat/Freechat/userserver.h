/*
***Copyright (C) 2019 Freechat Inc
***Contact: bogdyname@gmail.com
*/

#ifndef USERSERVER_H
#define USERSERVER_H


#include <QtNetwork>
#include <QSctpServer>
#include <QHostAddress>

class Connection;

class Server : public QSctpServer
{
    Q_OBJECT

public:
        QSctpServer(QObject *parent = nullptr);

signals:
        void NewConnection(Connection *connection);

protected:
        void InComingConnection(qintptr socketDescription) override;
};

#endif // USERSERVER_H
