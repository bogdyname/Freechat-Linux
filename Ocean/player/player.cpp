/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
***Created by bogdyname
***Created by Valentiy
*/

#include "player.h"

Player::Player(QObject *parent)
    : QMediaPlayer(parent)
{
    //setting up variable to switch status of track (play or pause)
    counterOfPausePlay = 0;

    this->setNotifyInterval(500);

    //player data
    connect(this, &QMediaPlayer::positionChanged, this, &Player::ChangedPosition);

    return;
}

Player::~Player()
{
    qDebug() << "Destructor from Player.cpp";
}

//Public slots
void Player::SetPausePlayTrack()
{
    counterOfPausePlay == 1 ? --counterOfPausePlay : ++counterOfPausePlay ;

    switch(counterOfPausePlay)
    {
        //Play current track
        case 0:
        {
            this->play();
            emit this->CallOutSetImagePuasePlayTrack(0);
        }
        break;

        //Pause current track
        case 1:
        {
            this->pause();
            emit this->CallOutSetImagePuasePlayTrack(1);
        }
        break;
    }

    return;
}

void Player::CallSetPlayList(QMediaPlaylist *playlist)
{
    if(SetPlayList(playlist))
        qDebug() << "set playlist";
    else
        qDebug() << "error: set playlist";

    return;
}

void Player::CallSetVolume(const int &volume)
{
    if(SetVolume(volume))
        qDebug() << "set volume" << volume;
    else
        qDebug() << "error: set volume";

    return;
}

qint64 Player::GetCurrentPosition()
{
    return this->currentPosition;
}

void Player::ChangedPosition(qint64 position)
{
    currentPosition = position;

    return;
}

bool Player::SetPlayList(QMediaPlaylist *playlist)
{
    if(!playlist->isEmpty())
    {
        this->setPlaylist(playlist);
        return true;
    }
    else
        return false;
}

bool Player::SetVolume(const int &volume)
{
    if(volume > 0)
    {
        this->setVolume(volume);
        return true;
    }
    else
        return false;
}
