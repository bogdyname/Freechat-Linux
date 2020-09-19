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
    try
    {
        player = new QMediaPlayer(this);
    }
    catch(std::bad_alloc &exp)
    {
        qCritical() << "Exception caught: " << exp.std::bad_alloc::what();
        exit(1);
    }
    catch(...)
    {
        qCritical() << "Some exception caught";
        exit(1);
    }

    //setting up variables
    counterOfPausePlay = 0;

    player->setNotifyInterval(500);

    //player data
    connect(this, &QMediaPlayer::positionChanged, this, &Player::ChangedPosition);

    //catch error
    connect(this, static_cast<void(QMediaPlayer::*)(QMediaPlayer::Error )>(&QMediaPlayer::error), this, &Player::MediaError);
    //signals of error
    connect(this, &Player::CallOutNoError, this, &Player::NoError);
    connect(this, &Player::CallOutResourceError, this, &Player::ResourceError);
    connect(this, &Player::CallOutFormatError, this, &Player::FormatError);
    connect(this, &Player::CallOutNetworkError, this, &Player::NetworkError);
    connect(this, &Player::CallOutAccessDeniedError, this, &Player::AccessDeniedError);
    connect(this, &Player::CallOutServiceMissingError, this, &Player::ServiceMissingError);

    return;
}

Player::~Player()
{
    qDebug() << "Destructor from Player.cpp";
}

//Private slots
void Player::NoError(QMediaPlayer::Error errorStatus)
{

    return;
}

void Player::ResourceError(QMediaPlayer::Error errorStatus)
{

    return;
}

void Player::FormatError(QMediaPlayer::Error errorStatus)
{

    return;
}

void Player::NetworkError(QMediaPlayer::Error errorStatus)
{

    return;
}

void Player::AccessDeniedError(QMediaPlayer::Error errorStatus)
{

    return;
}

void Player::ServiceMissingError(QMediaPlayer::Error errorStatus)
{

    return;
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

void Player::ChangedPosition(qint64 position)
{
    currentPosition = position;

    return;
}

void Player::MediaError(QMediaPlayer::Error error)
{
    //error catch
    switch(error)
    {
        case QMediaPlayer::NoError: emit this->CallOutNoError(error); break;
        case QMediaPlayer::ResourceError: emit this->CallOutResourceError(error); break;
        case QMediaPlayer::FormatError: emit this->CallOutFormatError(error); break;
        case QMediaPlayer::NetworkError: emit this->CallOutNetworkError(error); break;
        case QMediaPlayer::AccessDeniedError: emit this->CallOutAccessDeniedError(error); break;
        case QMediaPlayer::ServiceMissingError: emit this->CallOutServiceMissingError(error); break;
        default: break;
    }

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
