/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef USERCLIENT_H
#define USERCLIENT_H

#include "userserver.h"
#include <QAbstractSocket>
#include <QHostAddress>
#include <QHash>

class PeerManager;

class UserClient : public QObject
{
    Q_OBJECT

public:
    UserClient();

    QString nickName() const;
    void sendMessage(const QString &message);
    bool hasConnection(const QHostAddress &senderIp, int senderPort = -1) const;

signals:
    void newParticipant(const QString &nick);
    void participantLeft(const QString &nick);
    void newMessage(const QString &from, const QString &message);

private slots:
    void readyForUse();
    void disconnected();
    void newConnection(Connection *connection);
    void connectionError(QAbstractSocket::SocketError socketError);

private:
    void removeConnection(Connection *connection);

    UserServer userserver;
    PeerManager *peerManager;
    QMultiHash<QHostAddress, Connection *> peers;
};
#endif // USERCLIENT_H
