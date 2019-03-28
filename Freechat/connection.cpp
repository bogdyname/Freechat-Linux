/*
***Copyright (C) 2019 Softwater Inc
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


    QObject::connect(this, SIGNAL(readyRead()),
                     this, SLOT(readyToRead()));
    QObject::connect(this, SIGNAL(disconnected()),
                     &pingTimer, SLOT(stop()));
    QObject::connect(&pingTimer, SIGNAL(timeout()),
                     this, SLOT(pingStatus()));
    QObject::connect(this, SIGNAL(connected()),
                     this, SLOT(checkConnection()));
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
    {
        return false;
    }
    else
    {
        /*CLEAR CODE*/
    }

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
        timerIdForTimerEvent();
    }
    else
    {
        /*CLEAR CODE*/
    }
}

void Connection::timerIdForTimerEvent()
{
    killTimer(transferTimerId);
    transferTimerId = -1;
}

void Connection::readyToRead()
{
        reader.reparse();
        while (reader.lastError() == QCborError::NoError)
        {
            if (state == WaintinForConnection)
            {
                if (!reader.isArray())
                {
                    break;
                }
                else
                {
                    /*CLEAR CODE*/
                }

                reader.enterContainer();
                state = WritingForConnection;
            }
            else if (reader.containerDepth() == 1)
            {

                if (!reader.hasNext())
                {
                    reader.leaveContainer();
                    disconnectFromHost();
                    return;
                }
                else
                {
                    /*CLEAR CODE*/
                }

                if (!reader.isMap() || !reader.isLengthKnown() || reader.length() != 1)
                {
                reader.enterContainer();
                }
                else
                {
                    /*CLEAR CODE*/
                }
            }
            else if (currentDataType == Undefined)
            {
                if (!reader.isInteger())
                {
                    break;
                }
                else
                {
                    /*CLEAR CODE*/
                }

                currentDataType = MetaData(reader.toInteger());
                reader.next();
            }
            else
            {
                if (reader.isString())
                {
                    auto r = reader.readString();
                    buffer += r.data;
                    if (r.status != QCborStreamReader::EndOfString)
                    {
                        continue;
                    }
                    else
                    {
                        /*CLEAR CODE*/
                    }
                }
                else if (reader.isNull())
                {
                    reader.next();
                }
                else
                {
                    break;
                }

                reader.leaveContainer();

                if (transferTimerId != -1)
                {
                    killTimer(transferTimerId);
                    transferTimerId = -1;
                }
                else
                {
                    /*CLEAR CODE*/
                }

                if (state == WritingForConnection)
                {
                    if (currentDataType != PlainText)
                    {
                        break;
                    }
                    else
                    {
                        /*CLEAR CODE*/
                    }
                    processCheckConnection();
                }
                else
                {
                    processData();
                }
            }
        }

        if (reader.lastError() != QCborError::EndOfFile)
        {
            abort();
        }
        else
        {
            /*CLEAR CODE*/
        }

        if (transferTimerId != -1 && reader.containerDepth() > 1)
        {
            transferTimerId = startTimer(TransferTimeout);
        }
        else
        {
            /*CLEAR CODE*/
        }
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

    writer.startMap(1);
    writer.append(Ping);
    writer.append(nullptr);
    writer.endMap();
}

void Connection::checkConnection()
{
    writer.startArray();
    writer.startMap(1);
    writer.append(checkingConnection);
    writer.append(username);
    writer.endMap();
    isCheckConnection = true;

    if (!reader.device())
    {
        reader.setDevice(this);
    }
    else
    {
        /*CLEAR CODE*/
    }
}

void Connection::processCheckConnection()
{
    username = buffer + '@' + peerAddress().toString()
                + ':' + QString::number(peerPort());
    currentDataType = Undefined;
    buffer.clear();

    if (!isValid())
    {
        abort();
        return;
    }
    else
    {
        /*CLEAR CODE*/
    }

    if (!isCheckConnection)
    {
        checkConnection();
    }
    else
    {
        /*CLEAR CODE*/
    }

    pingTimer.start();
    pongTime.start();
    state = ReadyForConnection;
    emit readyForUse();
}

void Connection::processData()
{
    switch (currentDataType)
    {
    case PlainText:
        emit newMessage(username, buffer);
        break;
    case Ping:
        writer.startMap(1);
        writer.append(Pong);
        writer.append(nullptr);
        writer.endMap();
        break;
    case Pong:
        pongTime.restart();
        break;
    default:
        break;
    }

    currentDataType = Undefined;
    buffer.clear();
}
