/*
***Copyleft (C) 2019 Softwater, Inc
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
static const int TransferTimeout = 30 * 1000;

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
        Undefined,
        PlainText,
        Ping,
        Pong
    };

    Connection(QObject *parent = nullptr);
    Connection(qintptr socketDescriptor, QObject *parent = nullptr);
    ~Connection();

    QString ReturnVariableUsername() const;
    void TestMessage(const QString &message);
    bool SendMessage(const QString &message);

signals:
    void ReadyForUse();
    void NewMessage(const QString &from, const QString &message);

protected:
    void TimerEvent(QTimerEvent *timerEvent);
    void TimerIdForTimerEvent();

private slots:
    void ReadyToRead();
    void PingStatus();
    void CheckConnection();

private:
    bool HasEnoughData();
    void ProcessCheckConnection();
    void ProcessData();

     QCborStreamReader reader;
     QCborStreamWriter writer;
     QString checkingConnection;
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
