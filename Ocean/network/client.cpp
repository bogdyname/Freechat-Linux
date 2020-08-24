#include "client.h"

Client::Client()
{
    try
    {
        socket = new QTcpSocket(this);
    }
    catch(std::bad_alloc &exp)
    {
        qCritical() << "Exception caught: " << exp.std::bad_alloc::what();
        abort();
    }
    catch(...)
    {
        qCritical() << "Some exception caught";
        abort();
    }

    qDebug() << "A new socket created.";

    return;
}

Client::~Client()
{
    qDebug() << "Destructor from client.cpp";
}
