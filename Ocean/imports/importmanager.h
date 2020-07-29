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
#include <QList>
#include <QFileDialog>

#include <QDebug>
#include <QListWidgetItem>
#include <QCoreApplication>

class ImportManager : public QFile
{
    Q_OBJECT

public:
    ImportManager();
    ~ImportManager();

signals:
    //signal to emit it after QFileDialog to reboot default playlist (Ocean.cpp)
    void CallOutToCheckSongsInsideDefaultPlayList();

    //Save added files
    /*
        1) added via QFileDialog and deleted on system
        2) added via QFileDialog just copy
        3) added via Drag and Drop just copy
    */
    //Slots for call them in main UI file (Ocean.h/cpp)
public slots:
    void CallFileDialogWithDel();
    void CallFileDialogOnlyCopy();
    void SaveFileViaDragAndDrop(const QStringList &paths);

    //Get name with format of just added songs
public:
    const QStringList GetJustAddedSongs();

    //methods to add music into app
private:
    void SaveFilesIntoMusicFolderAndDeleteIt(const QStringList &paths);
    void SaveFilesIntoMusicFolderOnlyCopy(const QStringList &paths);

    //check or create 'music' dir
    bool CheckDir();

    //parser to remove current path
    QString GetNameOfSongFromCurrentPath(const QString nameOfSong);

    //Objects of Qt
private:
    QDir *musicDir = nullptr;
    QFile *mp3File = nullptr;
    QFileDialog *importerWindow = nullptr;
    QStringList justAddedSongs = {};
};

#endif
