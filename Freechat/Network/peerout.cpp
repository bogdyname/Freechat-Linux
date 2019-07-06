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

    connect(&showNetworkSettings, SIGNAL(CallNetwrokSettings()), this, SLOT(WriteIpAddressFromPeer()));
}

Peerout::~Peerout()
{
    delete socket;
}

void Peerout::WriteIpAddressFromPeer()
{
    bool ok;

        QString text = QInputDialog::getText(this, tr("Network settings"),
        tr("Write IP address of peer:"),
        QLineEdit::Normal, QDir::home().dirName(), &ok);

        if (ok && !text.isEmpty())
        {
            writeIpOfPeer->setText(text);
        }
        else
        {
            /*clear code*/
        }

        return;
}

void Peerout::DoConnect()
{
    socket = new QTcpSocket(this);

    socket->connectToHost(strWANip, 80);

        if(socket->waitForConnected(3000))
        {
            qDebug() << "Connected!";

            socket->write("DATA OF TEXT");
            socket->waitForBytesWritten(1000);
            socket->waitForReadyRead(3000);
            qDebug() << "Reading: " << socket->bytesAvailable();

            qDebug() << socket->readAll();

            socket->close();
        }
        else
        {
            qDebug() << "Not connected!";
        }

        return;
}

void Peerout::BytesWrittenOfData(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";

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
    qDebug() << "reading...";
    qDebug() << socket->readAll();

    return;
}
