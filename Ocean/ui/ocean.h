/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#ifndef OCEAN_H
#define OCEAN_H

#include <QTimer>
#include <QDebug>
#include <QLabel>
#include <QPixmap>
#include <QWidget>
#include <QSlider>
#include <QLineEdit>
#include <QComboBox>
#include <QListWidget>
#include <QPushButton>
#include <QMainWindow>
#include <QStringList>
#include <QMessageBox>
#include <QSpacerItem>
#include <QTextBrowser>
#include <QMediaPlayer>
#include <QResizeEvent>
#include <QMediaPlaylist>
#include "ui_ocean.h"

//widgets
#include "createplaylistwidget.h"

//managers
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

    /*----------------------------------------------------------------NOT DONE----------------------------------------------------------------*/

    //Context Menu of QListWidget
    //for musiclist widget
    void ShowContextMenuOfMusicList(const QPoint &point);//NOT DONE
    void EraseAllItemsFromMusicList();//NOT DONE
    void EraseItemFromMusicList();//NOT DONE
    //for playlist widget
    void ShowContextMenuOfPlayList(const QPoint &point);//NOT DONE
    void EraseItemFromPlayList();//NOT DONE
    void CreatePlaylist();//NOT DONE
    void RenamePlaylist();//NOT DONE
    void SavePlaylist();//NOT DONE

    //Work with managers of own classes
    void SetPlayList(QListWidgetItem *item);//NOT DONE

    //ui slots of create playlist widget
    void CloseWidgetViaCancel();//NOT DONE
    void CloseWidgetViaOkay(const QString &name);//NOT DONE

    //slots for timers
    //slot of timer-For-Check-Creat-List-Widget
    void IfCreateListWidgetClosed();//NOT DONE

    /*----------------------------------------------------------------NOT DONE----------------------------------------------------------------*/

private:
    //UI widgets
    //track status (maybe bit rank)
    QSlider *sliderOfTrack = nullptr;
    //right side (working with app)
    QSpacerItem *spacer = nullptr;
    QPixmap *ownImage = nullptr;
    QSlider *sliderOfVolume = nullptr;
    QLabel *imageOfPlayList = nullptr;
    QComboBox *sortBy = nullptr;
    //lists of playlists and musiclists
    QListWidget *playLists = nullptr;
    QListWidget *musicList = nullptr;
    //player
    QPushButton *playTrack = nullptr;
    QPushButton *stopTrack = nullptr;
    QPushButton *nextTrack = nullptr;
    QPushButton *previousTrack = nullptr;
    //add music buttons
    QPushButton *buttonForAddMusicWithDel = nullptr;
    QPushButton *buttonForAddMusicOnlyCopy = nullptr;

    //ToolS for widgets
    QTimer *timerForCheckWidgetOfCreatPlayList = nullptr;

    //Own Objects
private:
    //ui
    CreatePlayListWidget *createPlayList = nullptr;

    //managers
    ImportManager *importManager = nullptr;
    Playlist *playlistmanager = nullptr;
    Player *playermanager = nullptr;

private:
    Ui::Ocean *ui;
};
#endif
