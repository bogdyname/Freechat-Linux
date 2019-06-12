/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "usernametable.h"
#include "connectionf2f.h"
#include "username.h"

ConnectionF2F::ConnectionF2F(QObject *parent)
    : QTcpSocket(parent)
{

}

ConnectionF2F::~ConnectionF2F()
{

}

Client::Client(QObject *parent)
    : QTcpSocket(parent)
{

}

Client::~Client()
{

}

Host::Host(QObject *parent)
    :QTcpServer(parent)
{

}

Host::~Host()
{

}
