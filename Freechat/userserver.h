/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef USERSERVER_H
#define USERSERVER_H

#include <QtNetwork>
#include <QTcpServer>
#include <QHostAddress>

class Connection;

class UserServer : public QTcpServer
{
    Q_OBJECT

public:
        UserServer(QObject *parent = nullptr);

signals:
        void NewConnection(Connection *connection);

protected:
        void InComingConnection(qintptr socketDescription) override;
};

#endif // USERSERVER_H
