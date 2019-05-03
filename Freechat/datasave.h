/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef DATASAVE_H
#define DATASAVE_H

#include <QTextStream>
#include <QSaveFile>
#include <QIODevice>
#include <QTimer>
#include <QFile>

class Username;

class Datasave : public QFile
{
    Q_OBJECT

public:
    QFile fileWithData;
    QFile fileWithDataForBackup;

    QTimer runTimer;
    QByteArray block;

public:
    Datasave(QObject *parent = nullptr);

signals:
    void RunTimeIsOver();
    void SaveDataFileAs();
    void UpToBeginOfFile();
    void DropToEndOfFile();
    void CheckYourMemorySize();
    void CheckUsernameForSaveFile();

public slots:
    void DeleteAllDataForFreeMemory();
    void RunBackupFiles();
    void ToBeginOfFile();
    void ToEndOfFile();

protected:
    bool CheckForFileExists();
    bool CheckForFileIsOpen();
};

#endif // DATASAVE_H
