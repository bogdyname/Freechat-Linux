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

    //signal to emit it after delete selected song from app (Ocean.cpp)
    void CallOutDeleteTrackFromAllPlayListThereIsIt(const QString &song);

    //signals to delete music from app
    void CallOutDeleteMusicFromApp(const QString &song);
    void CallOutDeleteAllMusicFromApp();

    //Slots for call them in main UI file (Ocean.h/cpp)
public slots:
    void CallFileDialogWithDel();
    void CallFileDialogOnlyCopy();

    //slots to
private slots:
    void DeleteMusicFromApp(const QString &song);
    void DeleteAllMusicFromApp();

    //methods to add music into app
private:
    void SaveFilesIntoMusicFolderAndDeleteIt(const QStringList &pathsOfmp3);
    void SaveFilesIntoMusicFolderOnlyCopy(const QStringList &pathsOfmp3);

    //check or create 'music' dir
    bool CheckDir();

    //methods to delete selected or all music
    bool DeleteMusic(const QString &song);
    bool DeleteAllMusic();

    //parser
    QString GetNameOfSongFromCurrentPath(const QString nameOfSong);

    //Objects of Qt
private:
    QDir *musicDir = nullptr;
    QFile *mp3File = nullptr;
    QFileDialog *importerWindow = nullptr;
};

#endif
