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
#include "getstringwidget.h"

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

    /*-------------------------------------------this->QWidget------------------------------------------*/

    // Events for MainWindow
    /*
        1) for check resize of MainWindow
    */
protected:
    virtual void resizeEvent(QResizeEvent *event);

signals:
    void CallOutPassNamesOfSongsToMusicList(const QStringList &songs);

    // Slots for MainWindow
    /*
        1) Slot for hide widgets inside MainWindow
        2) Slot for show widgets inside MainWindow
    */
private slots:
    void Hidder();
    void Shower();
    void GetNamesOfSongsToMusicList(QListWidgetItem *item);
    void PassNamesOfSongsToMusicList(const QStringList &songs);
    /*-------------------------------------------this->QWidget------------------------------------------*/


    /*---------------------------------------------MANAGERS-------------------------------------------*/
    /*
        1) Context Menu of Music list
        2) Context Menu of Playlists
        3) Slots for Ocean::playlistmanager
    */

    // Context Menu of Music list ------------------------------------------------- 1
    //Slot for call and create context menu for Music list (right click on item of Ocean::musicList)
    void ShowContextMenuOfMusicList(const QPoint &point);

    // SLOTS for context menu of music list
    /*
        1) Delete all songs
        2) Delete one selected item
    */
    void EraseAllItemsFromMusicList();
    void EraseItemFromMusicList();
    // Context Menu of Music list ------------------------------------------------- 1

    // Context Menu of Playlists -------------------------------------------------- 2
    //Slot for call and create context menu for Playlist (right click on item of Ocean::playLists)
    void ShowContextMenuOfPlayList(const QPoint &point);

    // SLOTS for context menu of Playlists
    /*
        1) Delete item from QListWidget (Ocean::playLists)
        2) Create playlist via own widget (Ocean::getStringFromUser)
        3) Rename playlist via own widget (Ocean::getStringFromUser)
        4) Save playlist via own object for QMediaPlaylist (Ocean::playlistmanager)
    */
    void EraseItemFromPlayList();
    void CreatePlaylist();
    void RenamePlaylist();
    void SavePlaylist();
    // Context Menu of Playlists -------------------------------------------------- 2

    // SLOTS for managers --------------------------------------------------------- 3
    // Slot for set Playlist
    void SetPlayList(QListWidgetItem *item);
    // SLOTS for managers --------------------------------------------------------- 3

    /*---------------------------------------------MANAGERS-------------------------------------------*/


    /*-----------------------------------------------UI-----------------------------------------------*/

    /*
       1) Widget for get string from user
       2) widget for info of song
    */

    // Widget for get string from user -------------------------------------------- 1
    /*
        1) Close widget via 'cancel button' without string
        2) Close widget via return pressed and pass string from user
    */
    void CloseWidgetForGetStringViaCancel();
    void CloseWidgetForGetStringViaOkay(const QString &name);
    // Widget for get string from user -------------------------------------------- 1

    /*-----------------------------------------------UI-----------------------------------------------*/


    /*---------------------------------------------Tools---------------------------------------------*/

    /*
        1) Timer for Ocean::getStringFromUser
    */

    // Timer for Ocean::getStringFromUser ----------------------------------------- 1
    void IfCreateListWidgetClosed();
    // Timer for Ocean::getStringFromUser ----------------------------------------- 1

    /*---------------------------------------------Tools---------------------------------------------*/

private:
    //UI--------------------------------------------------------------
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
    //UI--------------------------------------------------------------

    //TOOLS-----------------------------------------------------------
    //ToolS for widgets
    QTimer *timerForCheckWidgetOfCreatPlayList = nullptr;
    //TOOLS-----------------------------------------------------------


    //Own Objects-----------------------------------------------------

    /*
        1) UI own widgets
        2) Managers
    */
private:
    // UI own widgets ----------------------------------------------- 1
    //ui widgets
    GetStringWidget *getStringFromUser = nullptr;
    // UI own widgets ----------------------------------------------- 1

    // Managers ----------------------------------------------------- 2
    ImportManager *importManager = nullptr;
    Playlist *playlistmanager = nullptr;
    Player *playermanager = nullptr;
    // Managers ----------------------------------------------------- 2
    //Own Objects-----------------------------------------------------


    //default UI
private:
    Ui::Ocean *ui;
};
#endif
