/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef VIDEOVIEWER_H
#define VIDEOVIEWER_H

#include <QMediaPlayer>
#include <QVideoWidget>
#include <QWidget>

class Multibedia;
class QAbstractButton;
class QSlider;
class QLabel;
class QUrl;

class Videoviewer : public QWidget
{
    Q_OBJECT

public:
    Videoviewer();
    Videoviewer(QWidget *parent = nullptr);
    ~Videoviewer();

    void SetUrl(const QUrl &url);

public slots:
    void OpenFile();
    void Play();

private slots:
    void MediaStateChanged(QMediaPlayer::State state);
    void PositionChanged(qint64 position);
    void DurationChanged(qint64 duration);
    void SetPosition(int position);
    void HandleError();

private:
    QMediaPlayer* m_mediaPlayer;
    QAbstractButton *m_playButton;
    QSlider *m_positionSlider;
    QLabel *m_errorLabel;
};

#endif // VIDEOVIEWER_H
