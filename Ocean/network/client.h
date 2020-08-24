#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>

class Client : public QTcpSocket
{
    Q_OBJECT

public:
    Client();
    ~Client();

private:
    QTcpSocket *socket = nullptr;
};

#endif
