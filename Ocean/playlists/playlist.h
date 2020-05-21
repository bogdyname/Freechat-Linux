/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
***Created by bogdyname
*/

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QUrl>
#include <QDir>
#include <QFile>
#include <QList>
#include <QString>
#include <QStringList>
#include <QFileDialog>
#include <QMediaObject>
#include <QMediaPlaylist>
#include <QCoreApplication>

class Playlist : public QMediaPlaylist
{
    Q_OBJECT

    /*
     * Format of playlists = .m3u
     * Dir 'bin' for saving and loading playlists
    */

public:
    Playlist();
    ~Playlist();

signals:
    void SetCurrentPlayList(QMediaPlaylist *currentPlaylist);
    void SetDefaultPlayList(QMediaPlaylist *defaultPlaylist);
    void CallOutSaveCurrentPlayList(const QString &name, const QStringList &newListOfSongs);
    void CallOutSaveSelectedPlayList(const QString &name, const QStringList &newListOfSongs, QMediaPlaylist *currentPlaylist);
    void CallOutRenameCurrentPlayList(QString &newName, QMediaPlaylist *currentPlaylist);
    void CallOutRenameSelectedPlayList(const QString &newName, const QString &currentName);

public slots:
    void SaveCurrentPlayList(const QString &name, const QStringList &newListOfSongs, QMediaPlaylist *currentPlaylist);
    void SaveSelectedPlayList(const QString &name, const QStringList &newListOfSongs);
    void CreateCurrentPlayList(const QString &name);
    void RemoveCurrentPlayList(const QString &name);
    void RenameCurrentPlayList(const QString &newName, QMediaPlaylist *currentPlaylist);
    void RenameSelectedPlayList(const QString &newName, const QString &currentName);

public:
    QMediaPlaylist* GetCurrentPlayList();
    QMediaPlaylist* GetDefaultPlayList();
    void LoadDefaultPlayList();
    void LoadPlayList(const QString &name);

    //check out these methods
private:
    bool CreatePlayList(const QString &name, const QStringList &list, QMediaPlaylist *currentPlaylist);
    bool RemovePlayList(const QString &name);
    bool LookingForPlayList(const QString &name, QMediaPlaylist *medialist);
    bool CreateDefaultPlaylist(QMediaPlaylist *medialist);
    bool SavePlaylist(const QString &name, const QStringList &newListOfSongs, QMediaPlaylist *currentPlaylist);
    bool SavePlaylist(const QString &name, const QStringList &newListOfSongs);
    bool RenamePlayList(const QString &newName, QMediaPlaylist *currentPlaylist); //for current playlist
    bool RenamePlayList(const QString &newName, const QString &currentName); //for playlist from bin dir
    bool CheckSettingsDir();

private:
    QFileDialog *dialog = nullptr;
    QDir *settingsDir = nullptr;
    QStringList list;
    QStringList allSongs;
    QMediaPlaylist *currentPlaylist = nullptr;
    QMediaPlaylist *defaultPlaylist = nullptr;
};

#endif
