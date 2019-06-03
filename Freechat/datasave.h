/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef DATASAVE_H
#define DATASAVE_H

#include "ui_freechat.h"
#include <QStorageInfo>
#include <QTextStream>
#include <QSaveFile>
#include <QIODevice>
#include <QDateTime>
#include <QTimer>
#include <QFile>

class Username;
class Freechat;

class Datasave : public QFile
{
    Q_OBJECT

public:
    QTimer runTimer;
    QByteArray block;

    QStorageInfo storage = QStorageInfo::root();

public:
    Datasave(QObject *parent = nullptr);

signals:
    void RunTimeIsOver();
    void SaveDataFileAs();
    void CheckYourMemorySize();
    void ReadFileForViewMessages();
    void CheckUsernameForSaveFile();

public slots:
    void DeleteAllDataForFreeMemory(QFile &fileWithData, QFile &fileWithDataForBackup);
    void RunBackupFiles(QFile &fileWithData, QFile &fileWithDataForBackup);
    void ReadFile(QFile &fileWithData);

protected:
    inline bool CheckForFileExists(QFile &fileWithData);
    inline bool CheckForFileIsOpen(QFile &fileWithData);
};

#endif // DATASAVE_H
