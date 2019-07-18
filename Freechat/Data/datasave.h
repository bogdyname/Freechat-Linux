/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef DATASAVE_H
#define DATASAVE_H

#include "Bin/freechat.h"
#include "Network/connectionf2f.h"
#include <QStorageInfo>
#include <QDateTime>
#include <QTimer>
#include <QFile>

class Datasave : public QFile,
private ConnectionF2F, private Freechat
{
    Q_OBJECT

private:
    QByteArray *buffer = nullptr;
    QStorageInfo storage = QStorageInfo::root();

public:
    ~Datasave();
    Datasave(Freechat *parent = nullptr);
    Datasave(QFile &fileWithData, QFile &fileWithDataForBackup);

signals:
    void CheckYourMemorySize();
    void ReadFileForViewMessages();
    void ChooseFileWithData(QFile &fileWithData);

private slots:
    inline void DeleteAllDataForFreeMemory(QFile &fileWithData, QFile &fileWithDataForBackup);
    void RunBackupFiles(QFile &fileWithData, QFile &fileWithDataForBackup);
    inline void ReadFile(QFile &fileWithData);
    void OpenFile(QFile &fileWithData);

private:
    void RSAMODULE(QFile &fileWithData);
    inline bool CheckIpAddressForSaveFile(QString &strWithIpOfPeer);
    inline QString ReadFirstStringFromDataFile(QString &strWithIpOfPeer);
};
#endif
