/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef PEEROUT
#define PEEROUT

#include "Network/connectionf2f.h"
#include "Bin/freechat.h"

class Peerout : public ConnectionF2F
{
    Q_OBJECT

public:
    Peerout();
    ~Peerout();

protected slots:
    void WriteIpAddressFromPeer();

public slots:
    void ReadyRead();
    void DoConnect();
    void Connected();
    void Disconnected();
    void TaskResult(unsigned int Number);
    void BytesWrittenOfData(qint64 bytes);

private:
    QTcpSocket *socket = nullptr;
    QString strWANip;
};
#endif
