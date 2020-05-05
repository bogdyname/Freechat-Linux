/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
***Created by bogdyname
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

    //Slots for call them in main UI file (Ocean.h/cpp)
public slots:
    void CallFileDialogWithDel();
    void CallFileDialogOnlyCopy();

    void DeleteMusic();//Not done

private:
    void SaveFilesIntoMusicFolderAndDeleteIt(const QStringList &pathsOfmp3);
    void SaveFilesIntoMusicFolderOnlyCopy(const QStringList &pathsOfmp3);

    bool CheckDir();
    QString GetNameOfSongFromCurrentPath(const QString nameOfSong);

    bool DeleteMusicFromMusicFolder();//Not done

    //Objects of Qt
private:
    QDir *musicDir = nullptr;
    QFile *mp3File = nullptr;
    QFileDialog *importerWindow = nullptr;
};

#endif
