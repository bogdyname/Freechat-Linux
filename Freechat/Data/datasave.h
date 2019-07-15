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

public slots:
    inline void DeleteAllDataForFreeMemory(QFile &fileWithData, QFile &fileWithDataForBackup);
    void RunBackupFiles(QFile &fileWithData, QFile &fileWithDataForBackup);
    inline void ReadFile(QFile &fileWithData);
    void OpenFile(QFile &fileWithData);

private:
    void RSAMODULE(QFile &fileWithData);
    inline bool CheckIpAddressForSaveFile(QString &strWithIpOfPeer);
};
#endif
