/*
***Copyright (C) 2019 Freechat Inc
***Contact: bogdyname@gmail.com
*/

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtNetwork>
#include <QCborStreamReader>
#include <QCborStreamWriter>
#include <QElapsedTimer>
#include <QHostAddress>
#include <QSctpSocket>
#include <QTcpSocket>
#include <QString>
#include <QTimer>

static const int PingInterval = 5 * 1000;
static const int MaxBufferSize = 1024000;
static const int PongTimeout = 60 * 1000;

class Connection : public QTcpSocket
{
    Q_OBJECT

public:
    enum ConnectionData
    {
        WaintinForConnection,
        WritingForConnection,
        ReadyForConnection
    };

    enum MetaData
    {
        AlreadyConnection,
        Username,
        Undefined,
        PlainText,
        Ping
    };

    Connection(QObject *parent = nullptr);
    Connection(qintptr socketDescriptor, QObject *parent = nullptr);
    ~Connection();

    QString returnVariableUsername() const;
    void testMessage(const QString &message);
    bool sendMessage(const QString &message);

signals:
    void readyForUse();
    void newMessage(const QString &from, const QString &message);

protected:
    void timerEvent(QTimerEvent *timerEvent);

private slots:
    void readyToRead();
    void pingStatus();
    void checkConnection();

private:
    bool hasEnoughData();
    void processCheckConnection();
    void processData();

     QCborStreamReader reader;
     QCborStreamWriter writer;
     QString username;
     QTimer pingTimer;
     QElapsedTimer pongTime;
     QString buffer;
     ConnectionData state;
     MetaData currentDataType;
     int transferTimerId;
     bool isCheckConnection;

};

#endif // CONNECTION_H
