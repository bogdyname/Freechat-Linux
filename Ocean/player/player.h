/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
***Created by bogdyname
***Created by Valentiy
*/

#ifndef PLAYER_H
#define PLAYER_H

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
    void CallSetMod(const unsigned short int &mod);
    void CallSetPlayList(QMediaPlaylist *playlist);
    void CallSetVolume(const unsigned short int &volume);

public:
    const QMediaPlayer* GetPlayer();
    qint64 GetPositionOfTrack();
    void SetPositionOfTrack(const qint64 &position);

private:
    bool SetModOfPlayer(const unsigned short int &mod);
    bool SetPlayList(QMediaPlaylist *playlist);
    bool SetVolume(const unsigned short int &volume);

private:
    QMediaPlayer *player = nullptr;
};

#endif
