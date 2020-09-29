#include "client.h"

Client::Client(QTcpSocket *parent)
    :   QTcpSocket(parent), data(0)
{
    try
    {
        socket = new QTcpSocket(this);
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

    qDebug() << "A new socket created.";

    connect(this, &QAbstractSocket::connected, this, &Client::Connected);
    connect(this, &QAbstractSocket::readyRead, this, &Client::ReadyRead);
    connect(this, &QAbstractSocket::errorOccurred, this, &Client::Error);

    //Settin up variables
    error = "";

    return;
}

Client::~Client()
{
    qDebug() << "Destructor from client.cpp";
}

void Client::Connected()
{
    //Need to send size of data to check free space for it on server PC

    #ifndef Q_DEBUG
    qDebug() << "Connected.";
    #endif

    return;
}


void Client::Error(QAbstractSocket::SocketError err)
{
    error.clear();

    //Find error
    error = "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                                    "The host was not found.\n" : err == QAbstractSocket::RemoteHostClosedError ?
                                    "The remote host is closed.\n" : err == QAbstractSocket::ConnectionRefusedError ?
                                    "The connection was refused.\n" : QString(socket->errorString() + "\n"));

    //Trigger error signal
    emit this->CallOutSendError(error);

    return;
}

void Client::SendData(QFile &file)
{
    QByteArray fileData = 0; //Buffer of guts of file
    QByteArray dataBlock = 0; //Full buffer
    //Setting up stream
    QDataStream sendStream(&dataBlock, QIODevice::WriteOnly);
    sendStream.QDataStream::setVersion(QDataStream::Qt_5_9);

    if(socket->state() != QAbstractSocket::ConnectedState || file.open(ReadOnly))
    {
        //Write name of file
        sendStream << (quint64)0 << file.fileName();

        //Write guts of file
        fileData = file.readAll();
        //Write guts of file into one buffer
        dataBlock.append(fileData);

        //Set stream on NIL position
        sendStream.device()->seek(0);
        //Write block of qint64
        sendStream << (quint64 )(dataBlock.size() - sizeof(932838457459459));

        //Check recieved and replied sizes
        qint64 sendData = 0;
        while (sendData < dataBlock.size())
        {
            //Write data into socket
            qint64 checkData = socket->write(dataBlock);
            //Save writed data
            sendData += checkData;
        }
    }

    return;
}
