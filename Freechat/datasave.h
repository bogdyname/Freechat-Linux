/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef DATASAVE_H
#define DATASAVE_H

#include <QTextStream>
#include <QSaveFile>
#include <QIODevice>
#include <QWidget>
#include <QTimer>
#include <QFile>

class Freechat;
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

    bool CheckForFileExists();

signals:
    void CheckYourMemorySize();
    void CheckUsernameForSaveFile();
    void UpToBeginOfFile();
    void DropToEndOfFile();
    void RunTimeIsOver();

public slots:
    void AbortProgWheneverMemorySizeFull();
    void SaveFileForUsername();
    void RunBackupFiles();
    void ToBeginOfFile();
    void ToEndOfFile();
};

#endif // DATASAVE_H
