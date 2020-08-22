/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
***Created by bogdyname
***Created by Valentiy
*/

#include "player.h"

Player::Player()
{
    try
    {
        player = new QMediaPlayer(this);
    }
    catch(std::bad_alloc &exp)
    {
        #ifndef Q_DEBUG
        qCritical() << "Exception caught: " << exp.std::bad_alloc::what();
        #endif
        abort();
    }
    catch(...)
    {
        #ifndef Q_DEBUG
        qCritical() << "Some exception caught";
        #endif
        abort();
    }

    player->setNotifyInterval(500);

    connect(this, &QMediaPlayer::positionChanged, this, &Player::ChangedPosition);
    connect(this, static_cast<void(QMediaPlayer::*)(QMediaPlayer::Error )>(&QMediaPlayer::error), this, &Player::MediaError);

    return;
}

Player::~Player()
{
    qDebug() << "Destructor from Player.cpp";
}

//Public slots
void Player::SetPausePlayTrack()
{
    static int counter = 0;

    counter == 1 ? --counter : ++counter ;

    switch(counter)
    {
        //Play current track
        case 0:
        {
            this->play();
            emit this->CallOutSetImagePuasePlayTrack(0);
            qDebug() << 0 ;
        }
        break;

        //Pause current track
        case 1:
        {
            this->pause();
            emit this->CallOutSetImagePuasePlayTrack(1);
            qDebug() << 1 ;
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

void Player::ChangedPosition(qint64 position)
{
    currentPosition = position;

    return;
}

void Player::MediaError(QMediaPlayer::Error)
{
    //check it out

    emit this->CallOutNoError();
    emit this->CallOutResourceError();
    emit this->CallOutFormatError();
    emit this->CallOutNetworkError();
    emit this->CallOutAccessDeniedError();
    emit this->CallOutServiceMissingError();

    return;
}

//Methods
const QMediaPlayer* Player::GetPlayer()
{
    return player;
}

qint64 Player::GetPositionOfTrack()
{
    return currentPosition;
}

void Player::SetPositionOfTrack(const qint64 position)
{
    player->setPosition(position);

    return;
}

bool Player::SetPlayList(QMediaPlaylist *playlist)
{
    if(!playlist->isEmpty())
    {
        player->setPlaylist(playlist);
        return true;
    }
    else
        return false;
}

bool Player::SetVolume(const int &volume)
{
    if(volume > 0)
    {
        player->setVolume(volume);
        return true;
    }
    else
        return false;
}
