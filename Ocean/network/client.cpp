#include "client.h"

Client::Client(QTcpSocket *parent)
    :   QTcpSocket(parent)
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

    return;
}

Client::~Client()
{
    qDebug() << "Destructor from client.cpp";
}
