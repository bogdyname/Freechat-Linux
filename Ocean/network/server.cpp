/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
***Created by bogdyname
*/

#include "server.h"

Server::Server(QObject *parent)
    : QTcpServer(parent)
{
    try
    {
        server = new QTcpServer(this);
    }
    catch(std::bad_alloc &exp)
    {
        qCritical() << "Exception caught: " << exp.std::bad_alloc::what();
        exit(1);
    }
    catch(...)
    {
        qCritical() << "Some exception caught";
        exit(1);
    }

    //server is working here
    if (server->listen(QHostAddress::Any, 6666))
        qDebug() << "Server started!";
    else
    {
        qCritical() << "Server not started: " << QTcpServer::errorString();
        server->close();
    }

    //setting up server
    server->setMaxPendingConnections(1);

    return;
}

Server::~Server()
{
    qDebug() << "Destructor from server.cpp";

    return;
}

void Server::Receiver()
{
    nextBlockSize = 0;
    QByteArray buffer = 0;
    socket = (QTcpSocket*)sender();

    //stream to write data from socket into buffer
    QDataStream receiveStream(socket);
    receiveStream.setVersion(QDataStream::Qt_5_13);

    forever
    {
        if(nextBlockSize == 0)
        {
            if(socket->bytesAvailable() < sizeof(932838457459459))
                break;

            receiveStream >> nextBlockSize;
        }

        if(socket->bytesAvailable() < nextBlockSize)
            break;

        receiveStream >> buffer;

        nextBlockSize = 0;
    }

    /*
        Need to parse first data of ByteArray
        Pass it into ImportManager
    */

    return;
}

void Server::Sender()
{
    const QString messageDone = "received";
    QByteArray block;
    QDataStream sendStream(&block, QIODevice::ReadWrite);
    sendStream.setVersion(QDataStream::Qt_5_13);

    //write data into stream
    sendStream << qint64(0) << messageDone;

    //set sream in beginning
    sendStream.device()->seek(0);
    sendStream << (qint64)(block.size() - sizeof(932838457459459));

    //write data into socket and after that send it
    socket->write(block);
    socket->flush();

    return;
}
