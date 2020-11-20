/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
***Created by bogdyname
***Created by Valentiy
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <QTimer>
#include <QMediaObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class Player : public QMediaPlayer
{
    Q_OBJECT

public:
    Player(QObject *parent = nullptr);
    ~Player();

signals:
    void CallOutSetImagePuasePlayTrack(const int &counter);

public slots:
    void SetPausePlayTrack();
    void CallSetPlayList(QMediaPlaylist *playlist);
    void CallSetVolume(const int &volume);

public:
    qint64 GetCurrentPosition();

private slots:
    void ChangedPosition(qint64 position);

private:
    bool SetPlayList(QMediaPlaylist *playlist);
    bool SetVolume(const int &volume);

private:
    int counterOfPausePlay;
    qint64 currentPosition;
};

#endif
