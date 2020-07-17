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
    Player();
    ~Player();

public slots:
    void CallSetMod(const int &mod);
    void CallSetPlayList(QMediaPlaylist *playlist);
    void CallSetVolume(const int &volume);

private slots:
    void ChangedPosition(qint64 position);

public:
    const QMediaPlayer* GetPlayer();
    qint64 GetPositionOfTrack();
    void SetPositionOfTrack(const qint64 position);

private:
    bool SetModOfPlayer(const int &mod);
    bool SetPlayList(QMediaPlaylist *playlist);
    bool SetVolume(const int &volume);

private:
    QMediaPlayer *player = nullptr;
    qint64 currentPosition;
};

#endif
