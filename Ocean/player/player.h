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
    //Error signals
    void CallOutNoError(QMediaPlayer::Error errorStatus);
    void CallOutResourceError(QMediaPlayer::Error errorStatus);
    void CallOutFormatError(QMediaPlayer::Error errorStatus);
    void CallOutNetworkError(QMediaPlayer::Error errorStatus);
    void CallOutAccessDeniedError(QMediaPlayer::Error errorStatus);
    void CallOutServiceMissingError(QMediaPlayer::Error errorStatus);

private slots:
    //Error slots
    void NoError(QMediaPlayer::Error errorStatus);
    void ResourceError(QMediaPlayer::Error errorStatus);
    void FormatError(QMediaPlayer::Error errorStatus);
    void NetworkError(QMediaPlayer::Error errorStatus);
    void AccessDeniedError(QMediaPlayer::Error errorStatus);
    void ServiceMissingError(QMediaPlayer::Error errorStatus);

public slots:
    void SetPausePlayTrack();
    void CallSetPlayList(QMediaPlaylist *playlist);
    void CallSetVolume(const int &volume);

private slots:
    void ChangedPosition(qint64 position);
    void MediaError(QMediaPlayer::Error);

public:
    const QMediaPlayer* GetPlayer();
    qint64 GetPositionOfTrack();
    void SetPositionOfTrack(const qint64 position);

private:
    bool SetPlayList(QMediaPlaylist *playlist);
    bool SetVolume(const int &volume);

private:
    QMediaPlayer *player = nullptr;
    qint64 currentPosition;
};

#endif
