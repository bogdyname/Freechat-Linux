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
    QTimer *runTimer = nullptr;
    QByteArray *buffer = nullptr;

    QStorageInfo storage = QStorageInfo::root();

public:
    ~Datasave();
    Datasave(QObject *parent = nullptr);
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
};

#endif // DATASAVE_H
