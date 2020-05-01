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
#include <QLineEdit>
#include <QComboBox>
#include <QListWidget>
#include <QPushButton>
#include <QMainWindow>
#include <QStringList>
#include <QMessageBox>
#include <QTextBrowser>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "ui_ocean.h"

#include "imports/importmanager.h"

class Ocean : public QMainWindow, private Ui::Ocean
{
    Q_OBJECT

public:
    Ocean(QWidget *parent = nullptr);
    ~Ocean();

private:
    QLabel *imageOfPlayList = nullptr;
    QComboBox *sortBy = nullptr;
    QListWidget *playLists = nullptr;
    QListWidget *musicList = nullptr;
    QMediaPlayer *mediaPlayer = nullptr;
    QMediaPlaylist *mediaPlayList = nullptr;
    QPushButton *playTrack = nullptr;
    QPushButton *stopTrack = nullptr;
    QPushButton *nextTrack = nullptr;
    QPushButton *previousTrack = nullptr;
    QPushButton *buttonForAddMusicWithDel = nullptr;
    QPushButton *buttonForAddMusicOnlyCopy = nullptr;

    //Own Objects
private:
    ImportManager *importManager = nullptr;

private:
    Ui::Ocean *ui;
};
#endif
