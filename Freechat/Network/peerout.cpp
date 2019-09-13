/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "peerout.h"

Peerout::Peerout()
{
    socket = new QTcpSocket(this);

    #ifndef Q_DEBUG
    qDebug() << "A new socket created.";
    #endif

    connect(socket, SIGNAL(connected()), this, SLOT(Connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(Disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(ReadyRead()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(BytesWrittenOfData(qint64)));
}

Peerout::~Peerout()
{
    if(socket != nullptr)
    {
        delete socket;
    }
    else
    {
        /*clear code*/
    }
}

void Peerout::WriteIpAddressFromPeer()
{
    auto list = QHostInfo::fromName(QHostInfo::localHostName()).addresses();

    #ifndef Q_DEBUG
    qDebug() << "Addresses: " << list << endl;
    #endif

    //strWANip = ;

    return;
}

void Peerout::DoConnect()
{
    socket->connectToHost(ip, 80);

        if(socket->waitForConnected(3000))
        {
            Connected();

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

void Peerout::BytesWrittenOfData(qint64 &bytes)
{
    #ifndef Q_DEBUG
    qDebug() << bytes << " bytes written...";
    #endif

    return;
}

void Peerout::Connected()
{
    #ifndef Q_DEBUG
    qDebug() << "Connected!";
    #endif

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
