/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#ifndef OCEAN_H
#define OCEAN_H

#include <QDebug>
#include <QLabel>
#include <QWidget>
#include <QSlider>
#include <QLineEdit>
#include <QComboBox>
#include <QListWidget>
#include <QPushButton>
#include <QMainWindow>
#include <QStringList>
#include <QMessageBox>
#include <QTextBrowser>
#include <QMediaPlayer>
#include <QResizeEvent>
#include <QMediaPlaylist>
#include "ui_ocean.h"

#include "imports/importmanager.h"
#include "playlists/playlist.h"
#include "player/player.h"

class Ocean : public QMainWindow, private Ui::Ocean
{
    Q_OBJECT

public:
    Ocean(QWidget *parent = nullptr);
    ~Ocean();

protected:
    virtual void resizeEvent(QResizeEvent *event);

private slots:
    void Hidder();// NOT DONE
    void Shower();// NOT DONE

    //Context Menu of QListWidget
    void ShowContextMenuOfPlayList(const QPoint &point);// NOT DONE
    void ShowContextMenuOfMusicList(const QPoint &point);// NOT DONE
    void EraseItemFromMusicList();
    void EraseItemFromPlayList();

    //Work with managers of won classe
    void SetPlayList(QListWidgetItem *item);

private:
    QSlider *sliderOfTrack = nullptr;
    QSlider *sliderOfVolume = nullptr;
    QLabel *imageOfPlayList = nullptr;
    QComboBox *sortBy = nullptr;
    QListWidget *playLists = nullptr;
    QListWidget *musicList = nullptr;
    QPushButton *playTrack = nullptr;
    QPushButton *stopTrack = nullptr;
    QPushButton *nextTrack = nullptr;
    QPushButton *previousTrack = nullptr;
    QPushButton *buttonForAddMusicWithDel = nullptr;
    QPushButton *buttonForAddMusicOnlyCopy = nullptr;

    //Own Objects
private:
    ImportManager *importManager = nullptr;
    Playlist *playlistmanager = nullptr;
    Player *playermanager = nullptr;

private:
    Ui::Ocean *ui;
};
#endif
