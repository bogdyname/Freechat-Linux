/*
***Copyright (C) 2019 Freechat Inc
***Contact: bogdyname@gmail.com
*/

#include "usernametable.h"
#include "connection.h"
#include "username.h"

Connection::Connection(QObject *parent)
    : QTcpSocket(parent), writer(this)
{
    username = tr("unknown");
    state = WaintinForConnection;
    currentDataType = Undefined;
    transferTimerId = -1;
    isCheckConnection = false;
    pingTimer.setInterval(PingInterval);


    QObject::connect(this, SIGNAL(readyRead()), this, SLOT(readyToRead()));
    QObject::connect(this, SIGNAL(disconnected()), &pingTimer, SLOT(stop()));
    QObject::connect(&pingTimer, SIGNAL(timeout()), this, SLOT(pingStatus()));
    QObject::connect(this, SIGNAL(connected()),this, SLOT(checkConnection()));
}

Connection::Connection(qintptr socketDescriptor, QObject *parent)
    : Connection(parent)
{
    setSocketDescriptor(socketDescriptor);
    reader.setDevice(this);
}

QString Connection::returnVariableUsername() const
{
    return username;
}

bool Connection::sendMessage(const QString &message)
{
    if (message.isEmpty())
        return false;

    writer.startMap(1);
    writer.append(AlreadyConnection);
    writer.append(message);
    writer.endMap();
    return true;
}

void Connection::timerEvent(QTimerEvent *timerEvent)
{
    if(timerEvent->timerId() == transferTimerId)
    {
        abort();
        killTimer(transferTimerId);
        transferTimerId = -1;
    }
    else
    {
        /*CLEAR CODE*/
    }
}

void Connection::readyToRead()
{

}

void Connection::pingStatus()
{
    if(pongTime.elapsed() > PongTimeout)
    {
        abort();
        return;
    }
    else
    {
        /*CLEAR CODE*/
    }
}
