/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "peerin.h"

Peerin::Peerin(QObject *parent)
    : QTcpServer(parent)
{
    server = new QTcpServer(this);

    connect(server, SIGNAL(newConnection()), this, SLOT(SlotNewConnection()));

        if(server->listen(QHostAddress::Any, 3366))
        {
           #ifndef Q_DEBUG
           qDebug() << "Server: started";
           #endif
        }
        else
        {
            #ifndef Q_DEBUG
            qDebug() << "Server: not started: " << server->errorString();
            #endif

            server->close();
            return;
        }

        connect(server, SIGNAL(newConnection()), this, SLOT(SlotNewConnection()));

        return;
}

void Peerin::SlotNewConnection()
{
    QTcpSocket *clientSocket = server->nextPendingConnection();

    connect(clientSocket, SIGNAL(disconnect()), clientSocket, SLOT(deleteLater()));
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(SlotReadClient()));

    SendResponseToClient(clientSocket, Freechat::bufferOfMessages);

    return;
}

void Peerin::SlotReadClient()
{
    QTcpSocket *clientSocket = (QTcpSocket*)sender();
    QDataStream in(clientSocket);

    in.setVersion(QDataStream::Qt_5_12);

    for(;;)
    {
        if(!nextBlockSize)
        {
            if((clientSocket->bytesAvailable()) < (sizeof (quint16)))
            {
                break;
            }
            else
            {
                /*clear code*/
            }

            in >> nextBlockSize;
        }
        else
        {
            /*clear code*/
        }

        if((clientSocket->bytesAvailable()) < nextBlockSize)
        {
            break;
        }
        else
        {
            /*clear code*/
        }

        QTime time;
        QString strOfTime;
        in >> time >> strOfTime;

        QString strMessage = time.toString() + "Respons from peer: " + strOfTime;

        Freechat::viewField = strMessage;
        nextBlockSize = 0;

        SendResponseToClient(clientSocket, Freechat::bufferOfMessages);

    }

    return;
}

void Peerin::SendResponseToClient(QTcpSocket *socket, QString &messages)
{
    QByteArray block;

    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out << quint16(0) << QTime::currentTime() << messages;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof (quint16));

    socket->write(block);
    socket->flush();

    messages.clear();

    return;
}
