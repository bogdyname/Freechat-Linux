/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "peerout.h"

Peerout::Peerout()
{
    connect(socket, SIGNAL(Connected()), this, SLOT(Connected()));
    connect(socket, SIGNAL(DoConnect()), this, SLOT(DoConnect()));
    connect(socket, SIGNAL(ReadyRead()), this, SLOT(ReadyRead()));
    connect(socket, SIGNAL(BytesWrittenOfData(qint64)), this, SLOT(BytesWrittenOfData(qint64)));
}

Peerout::~Peerout()
{
    delete socket;
}

void Peerout::WriteIpAddressFromPeer()
{

        return;
}

void Peerout::DoConnect()
{
    socket = new QTcpSocket(this);

    socket->connectToHost(strWANip, 80);

        if(socket->waitForConnected(3000))
        {
            #ifndef Q_DEBUG
            qDebug() << "Connected!";
            #endif

            socket->write("DATA OF TEXT");
            socket->waitForBytesWritten(1000);
            socket->waitForReadyRead(3000);
            #ifndef Q_DEBUG
            qDebug() << "Reading: " << socket->bytesAvailable();
            qDebug() << socket->readAll();
            #endif

            socket->close();
        }
        else
        {
            #ifndef Q_DEBUG
            qDebug() << "Not connected!";
            #endif
        }

        return;
}

void Peerout::BytesWrittenOfData(qint64 bytes)
{
    #ifndef Q_DEBUG
    qDebug() << bytes << " bytes written...";
    #endif

    return;
}

void Peerout::Connected()
{

    return;
}

void Peerout::Disconnected()
{

    return;
}

void Peerout::ReadyRead()
{
    #ifndef Q_DEBUG
    qDebug() << "reading...";
    qDebug() << socket->readAll();
    #endif

    return;
}
