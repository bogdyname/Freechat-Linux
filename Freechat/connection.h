/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QCborStreamReader>
#include <QCborStreamWriter>
#include <QElapsedTimer>
#include <QHostAddress>
#include <QSctpSocket>
#include <QTcpSocket>
#include <QtNetwork>
#include <QString>
#include <QTimer>

class Username;

class Connection : public QTcpSocket
{

};

#endif // CONNECTION_H
