/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "ui_freechat.h"
#include "Bin/freechat.h"
#include "Network/connectionf2f.h"
#include <QStorageInfo>
#include <QDateTime>
#include <QTimer>
#include <QFile>

#ifndef DATASAVE_H
#define DATASAVE_H
class Datasave : public QFile,
public ConnectionF2F, public Freechat
{
    Q_OBJECT

private:
    QTimer *runTimer = nullptr;
    QByteArray *buffer = nullptr;

    QStorageInfo storage = QStorageInfo::root();

public:
    ~Datasave();
    Datasave(Freechat *parent = nullptr);
    Datasave(QFile &fileWithData, QFile &fileWithDataForBackup);

signals:
    void CheckYourMemorySize();
    inline void RunTimeIsOver();
    void ReadFileForViewMessages();
    void CheckIpAddressForSaveFile();

public slots:
    inline void DeleteAllDataForFreeMemory(QFile &fileWithData, QFile &fileWithDataForBackup);
    void RunBackupFiles(QFile &fileWithData, QFile &fileWithDataForBackup);
    inline void ReadFile(QFile &fileWithData);

private:
    void operator==();

private:
    void RSAMODULE();
};
#endif
