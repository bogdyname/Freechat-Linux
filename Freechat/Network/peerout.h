/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Network/connectionf2f.h"
#include <QWidget>
#include <QInputDialog>

#ifndef PEEROUT
#define PEEROUT
class Peerout : public ConnectionF2F
{
    Q_OBJECT

public:
    Peerout();
    ~Peerout();

signals:
    void CallNetwrokSettings();

protected slots:
    void WriteIpAddressFromPeer();

private slots:
    void ReadyRead();
    void DoConnect();
    void Connected();
    void Disconnected();
    void BytesWrittenOfData(qint64 bytes);

private:
    QTcpSocket *socket = nullptr;
    QString strWANip;
};
#endif
