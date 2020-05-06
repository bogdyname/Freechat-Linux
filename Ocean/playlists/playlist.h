/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
***Created by bogdyname
*/

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QDir>
#include <QFile>
#include <QList>
#include <QString>
#include <QFileDialog>
#include <QMediaObject>
#include <QMediaPlaylist>
#include <QCoreApplication>

class Playlist : public QFile, public QMediaPlaylist
{
    Q_OBJECT

public:
    Playlist();
    ~Playlist();

public slots:
    void GetCurrentPlayList();
    void CreateCurrentPlayList();
    void RemuveCurrentPlayList();

private:
    bool CreatePlayList(const QStringList &list, QMediaPlaylist *playlist);
    bool SavePlayListIntoFile();
    bool RemuvePlayListFromFile();
    bool LookingForListInFile();
    bool CheckSettingsDir();

private:
    QFileDialog *dialog = nullptr;
    QDir *settingsDir = nullptr;
    QFile *track = nullptr;
    QStringList list;
    QMediaPlaylist *playlist = nullptr;
};

#endif
