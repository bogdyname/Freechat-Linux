/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "peerout.h"

Peerout::Peerout(const QString &ipHost)
    : nextBlockSize(0)
{
    socket = new QTcpSocket(this);

    #ifndef Q_DEBUG
    qDebug() << "A new socket created.";
    #endif

    socket->connectToHost(ipHost, 3366);

    connect(socket, SIGNAL(connected()), this, SLOT(SlotConnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(SlotReadyRead()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(slotError(QAbstractSocket::SocketError)));
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

void Peerout::SlotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_12);

    for(;;)
    {
        if(!nextBlockSize)
        {
            if((socket->bytesAvailable() < (sizeof (quint16))))
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

        if((socket->bytesAvailable() < nextBlockSize))
        {
            break;
        }
        else
        {
             /*clear code*/
        }

        QTime time;
        QString str;
        in >> time >> str;


        // write data into variables for pass it in view field widget
        Freechat::viewField.append(time.toString() + " " + str);
        nextBlockSize = 0;
    }

    return;
}

void Peerout::SlotError(QAbstractSocket::SocketError err)
{
    QString strError =
            "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                         "The host was not found." :
                         err == QAbstractSocket::RemoteHostClosedError ?
                         "The remote host is closed." :
                         err == QAbstractSocket::ConnectionRefusedError ?
                         "The connection was refused." :
                         QString(socket->errorString()));

    // show error in view field
    Freechat::viewField.append(strError);

    return;
}

void Peerout::SlotSendToServer()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    // pass wroted data from line edit into socket through buffer
    out << quint16(0) << QTime::currentTime() << Freechat::bufferOfMessages;

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

    socket->write(block);
    socket->flush();

    Freechat::bufferOfMessages.clear();

    return;
}

void Peerout::SlotConnected()
{
    #ifndef Q_DEBUG
    qDebug() << "Connected.";
    #endif

    return;
}
