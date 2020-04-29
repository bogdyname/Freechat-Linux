/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#ifndef IMPORTMANAGER_H
#define IMPORTMANAGER_H

#include <QDir>
#include <QFile>
#include <QFileDialog>

#include <QDebug>
#include <QCoreApplication>

class ImportManager : public QFile
{
    Q_OBJECT

public:
    ImportManager();
    ~ImportManager();

private slots:
    //SavingFiles
    //for file dialog (looking for file in finder)
    void SaveFileIntoMusicFolder(const QString &pathOfmp3); //NOT DONE
    void SaveFilesIntoMusicFolder(const QStringList &pathsOfmp3); //NOT DONE

private:
    bool CheckDir();

    //Objects of Qt
private:
    QDir *musicDir = nullptr;
    QFile *mp3File = nullptr;
    QFileDialog *importerWindow = nullptr;
};

#endif
