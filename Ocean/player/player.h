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
    Q_CLASSINFO("Version", "1.0")

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
    int counterOfPausePlay;
    qint64 currentPosition;
};

#endif
