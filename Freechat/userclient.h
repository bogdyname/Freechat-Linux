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

    QString NickName() const;
    void SendMessage(const QString &message);
    bool HasConnection(const QHostAddress &senderIp, int senderPort = -1) const;

signals:
    void NewParticipant(const QString &nick);
    void ParticipantLeft(const QString &nick);
    void NewMessage(const QString &from, const QString &message);

private slots:
    void ReadyForUse();
    void Disconnected();
    void NewConnection(Connection *connection);
    void ConnectionError(QAbstractSocket::SocketError socketError);

private:
    void RemoveConnection(Connection *connection);

    UserServer userserver;
    PeerManager *peerManager;
    QMultiHash<QHostAddress, Connection *> peers;
};
#endif // USERCLIENT_H
