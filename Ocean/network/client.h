#ifndef CLIENT_H
#define CLIENT_H

#include <QFile>
#include <QTcpSocket>
#include <QDataStream>

class Client : public QTcpSocket
{
    Q_OBJECT
    Q_CLASSINFO("Version", "0.5")

public:
    explicit Client(QTcpSocket *parent = nullptr);
    ~Client();

signals:
    void CallOutSendError(const QString &error);
    void CallOutSendData(QFile &file);

private slots:
    void SendData(QFile &file);
    void ReadyRead();
    void Connected();
    void Error(QAbstractSocket::SocketError);

private:
    quint64 data;
    QString error;
    QTcpSocket *socket = nullptr;
};

#endif
