/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "ui_freechat.h"
#include "User/username.h"
#include "User/freechat.h"
#include <QStorageInfo>
#include <QDateTime>
#include <QTimer>
#include <QFile>

#ifndef DATASAVE_H
#define DATASAVE_H

class Datasave : public Username, public Freechat
{
    Q_OBJECT

private:
    QTimer *runTimer = nullptr;
    QByteArray *buffer = nullptr;

    QStorageInfo storage = QStorageInfo::root();

public:
    ~Datasave();
    Datasave(Freechat *parent = nullptr);
    Datasave(Datasave &&MoveSource, QFile &fileWithDataForBackup);
    Datasave(QFile &fileWithData, QFile &fileWithDataForBackup);

signals:
    void SaveDataFileAs();
    void CheckYourMemorySize();
    inline void RunTimeIsOver();
    void ReadFileForViewMessages();
    void CheckUsernameForSaveFile();

public slots:
    inline void DeleteAllDataForFreeMemory(QFile &fileWithData, QFile &fileWithDataForBackup);
    void RunBackupFiles(QFile &fileWithData, QFile &fileWithDataForBackup);
    inline void ReadFile(QFile &fileWithData);

private:
    void RSAMODULE();
};

#endif // DATASAVE_H
