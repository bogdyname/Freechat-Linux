/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include <QHostAddress>
#include <QJsonObject>
#include <QIODevice>
#include <QHostInfo>
#include <QSaveFile>
#include <QDateTime>
#include <QString>
#include <QFile>

#ifndef BIN_H
#define BIN_H
class Peerout;
class ConnectionF2F;

class Bin : public QObject
{
    Q_OBJECT

public:
    ~Bin();
    Bin(QObject *parent = nullptr);

signals:
    void RebootConnectin();

private slots:
    void SlotForRebootConnection();
};
#endif
