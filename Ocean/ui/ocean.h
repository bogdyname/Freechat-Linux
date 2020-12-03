/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#ifndef OCEAN_H
#define OCEAN_H

#include <QDir>
#include <QTimer>
#include <QDebug>
#include <QLabel>
#include <QPixmap>
#include <QWidget>
#include <QShortcut>
#include <QLineEdit>
#include <QMimeData>
#include <QMessageBox>
#include <QListWidget>
#include <QPushButton>
#include <QMainWindow>
#include <QStringList>
#include <QMessageBox>
#include <QSpacerItem>
#include <QTextBrowser>
#include <QMediaPlayer>
#include <QResizeEvent>
#include <QMediaContent>
#include <QMediaPlaylist>
#include <QAbstractItemView>
#include "ui_ocean.h"

//widgets
#include "addmusicwidget.h"
#include "getstringwidget.h"
#include "selectplaylist.h"

//custom widgets
#include "customWidgets/customlistwidget.h"
#include "customWidgets/slider.h"
#include "customWidgets/button.h"

//managers
#include "imports/importmanager.h"
#include "playlists/playlist.h"
#include "player/player.h"

//system
#include "sysmanager/system.h"
#include "sysmanager/system.cpp"

class Ocean : public QMainWindow, private Ui::Ocean
{
    Q_OBJECT

public:
    Ocean(QWidget *parent = nullptr);
    ~Ocean();

/****************************************************************************************************************************************/

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*||||||||||||||||||||||||||||||||||||||||||||||||||this->QWidget||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

    /*--------------------------------------Events for MainWindow--------------------------------*/

    /*
        1) for check resize of MainWindow
    */

protected:
    virtual void resizeEvent(QResizeEvent *event);
    /*--------------------------------------Events for MainWindow--------------------------------*/


    /*-------------------------------------Signals for playlist----------------------------------*/

    /*
        1) pass tracks into music list
        2) Create widget after widget for get string from user
    */

signals:
    void CallOutPassNamesOfSongsToMusicList(const QStringList &songs);
    void CallOutToCreateWindowThisWidgetToGetAddedTracks();
    /*-------------------------------------Signals for playlist----------------------------------*/


    /*-------------------------------------Slots for MainWindow----------------------------------*/

    /*
        1) Slot for hide widgets inside MainWindow
        2) Slot for show widgets inside MainWindow
        3) get names of tracks for QListWidget (music list)
        4) pass names of tracks for QListWidget (music list)
        5) add tracks after dropEvent
        6) set current index
        7) add playlist file after dropEvent
        8) media error checker
    */

private slots:
    void Hidder();
    void Shower();
    void GetNamesOfSongsToMusicList(QListWidgetItem *item);
    void PassNamesOfSongsToMusicList(const QStringList &songs);
    void AddFilesAfterDropEvent(const QStringList &files);
    void SetNameOfCurrentTrackFromPlaylist(const QString &name);
    void ErrorsByPlaylist(const int &error);
    /*-------------------------------------Slots for MainWindow----------------------------------*/

    /*-------------------------------------------Shortcut----------------------------------------*/


    /*
      * Shortcuts for window of app
        1) Full Window Shift + F
        2) Quit Window Shift + Q
        3) Hide Window Shift + H
    */

private slots:
    //Shortcuts for window of app
    void FullViaShiftF();
    void QuitViaShiftQ();
    void HideViaShiftH();
    /*-------------------------------------------Shortcut----------------------------------------*/

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*||||||||||||||||||||||||||||||||||||||||||||||||||this->QWidget||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/****************************************************************************************************************************************/

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||MANAGERS||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

    /*
        1) Context Menu of Music list
        2) Context Menu of Playlists
        3) Set play list (current after new tracks in app || or just set playlist by name)
    */

    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    // Context Menu of Music list ------------------------------------------------- 1
    //Slot for call and create context menu for Music list (right click on item of Ocean::musicList)
    void ShowContextMenuOfMusicList(const QPoint &point);

    // SLOTS for context menu of music list
    /*
        1) Delete all songs
        2) Delete one selected item
        3) Add song into playlist by name (pass data via SIGNAL of playlist manager)
        4) rename track (hot key or QMenu)
        5) rename track emit signal
        6) check widget after close to rename track
    */
    //delete all
    void EraseAllItemsFromMusicList();
    //delete
    void EraseItemFromMusicList();
    //add into playlist
    void AddSongIntoPlayListByIndex();
    //rename
    void RenameTrack();
    void RenameTrackByNewName();
    void ClosegetStringFromUserToRenameTrackViaCancel();
    //move track
    void MoveTrackUp();
    void MoveTrackDown();
    //parsing
    void ParseMusicList(const QString &name);
    // Context Menu of Music list ------------------------------------------------- 1

    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    // Context Menu of Playlists -------------------------------------------------- 2
    //Slot for call and create context menu for Playlist (right click on item of Ocean::playLists)
    void ShowContextMenuOfPlayList(const QPoint &point);

    // SLOTS for context menu of Playlists
    /*
        1) Delete item from QListWidget (Ocean::playLists)
        2) Create playlist via own widget (Ocean::getStringFromUser)
        3) Rename playlist via own widget and waiting user input (Ocean::getStringFromUser)
        3) Rename playlist after user input (Ocean::getStringFromUser)
        4) Export track into folder via QMenu
    */
    void EraseItemFromPlayList();
    void CreatePlaylist();
    void RenamePlaylist();
    void Rename();
    void ExportTrackOfPlayList();
    // Context Menu of Playlists -------------------------------------------------- 2

    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    // Set Playlist --------------------------------------------------------------- 3
    // Set Playlist
    void SetPlayList(QListWidgetItem *item);
    void SetPlayListByTrack(QListWidgetItem *item);
    void SetCurrentPlayList();
    // Set Playlist --------------------------------------------------------------- 3

    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||MANAGERS||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/****************************************************************************************************************************************/

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*||||||||||||||||||||||||||||||||||||||||||||||||||||||||UI|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

    /*
       1) Widget for get string from user
       2) Widget for get name of selected playlist
       3) Widget for info of song //Valenty
    */

    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    // Widget for get string from user -------------------------------------------- 1
    /*
        1) Close widget via 'cancel button' without string
        2) Close widget via return pressed and pass string from user (Create new playlist)
        3) Close widget via return pressed and pass string from user (Reaname playlist)
    */
    void ClosegetStringFromUserViaCancel();
    void ClosegetStringFromUserToCreatePlaylist();
    void ClosegetStringFromUserToRenameViaCancel();
    // Widget for get string from user -------------------------------------------- 1

    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    // Widget for get name of playlist from user ---------------------------------- 2
    /*
        1) Close widget after get name of selected playlist
        2) Close widget via 'cancel button'
    */
    void ClosegetStringWithSelectedPlaylist();
    void ClosegetStringWithSelectedPlaylistViaCancel();
    // Widget for get name of playlist from user ---------------------------------- 2

    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    // Widget for get added tracks from widget  ----------------------------------- 3
    /*
        1) Close widget via 'cancel button'
        2) Pass tracks into buffer
    */
    void ClosegetAddedTracksFromWidgetViaCancel();
    void PassAddedTracksIntoBuffer(const QStringList &list);
    // Widget for get added tracks from widget  ----------------------------------- 3

    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*||||||||||||||||||||||||||||||||||||||||||||||||||||||||UI|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/****************************************************************************************************************************************/

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*||||||||||||||||||||||||||||||||||||||||||||||||||||||Tools||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

    /*
        1) Timer for Ocean::getStringFromUserToCreateNewPlaylist
        2) Timer for Ocean::getStringFromUserToRenamePlaylist
        3) Timer for Ocean::getStringWithSelectedPlaylist
        4) Timer for Ocean::getAddedTracksFromWidget
        5) Get names of playlists from 'bin' dir
        6) Create widget after widget for get string from user
    */

    void IfgetStringFromUserClosed();//-----------------------------------------1
    void IfgetStringFromUserToRenameClosed();//---------------------------------2
    void IfgetStringWithSelectedPlaylistClosed();//-----------------------------3
    void IfgetAddedTracksFromWidgetClosed();//----------------------------------4
    QStringList GetNamesOfPlaylistsFromBinDir();//------------------------------5
    void CallWidgetAfterCreatePlaylistSlot();//---------------------------------6

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*||||||||||||||||||||||||||||||||||||||||||||||||||||||Tools||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/****************************************************************************************************************************************/

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||METHODS FOR UI||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

    /*
        1) get all items from list widget (alg)
    */

private:
    QStringList GetAllItemsFromList();
    QString GetCurrentNameOfTrack();

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||METHODS FOR UI||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/****************************************************************************************************************************************/

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||OBJECTS|||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

private:
    //UI--------------------------------------------------------------
    //track status (maybe bit rank)
    Slider *sliderOfTrack = nullptr;
    QLabel *nameOfTrack = nullptr;

    //right side (working with app)
    QSpacerItem *spacer = nullptr;
    QPixmap *ownImage = nullptr;
    Slider *sliderOfVolume = nullptr;
    QLabel *imageOfPlayList = nullptr;

    //lists of playlists and musiclists
    CustomListWidget *playLists = nullptr;
    CustomListWidget *musicList = nullptr;

    //player
    Button *pausePlayTrack = nullptr;
    Button *stopTrack = nullptr;
    Button *nextTrack = nullptr;
    Button *previousTrack = nullptr;
    Button *playbackMode = nullptr;

    //Error message box
    QMessageBox *errorMessageBox = nullptr;

    //Errors messages
    const QStringList errorsByPlayList =
    {
        "Can't save playlist",         //0
        "Can't rename playlist",       //1
        "Can't create playlist",       //2
        "Can't delete playlist",       //3
        "Can't rename track",          //4
        "Can't delete track",          //5
        "Can't add song into playlist",//6
        "Can't move song"              //7
    };
    //UI--------------------------------------------------------------

    //TOOLS-----------------------------------------------------------
    //ToolS for widgets
    QTimer *timerForCheckWidgets = nullptr;
    QStringList bufferOfAddedTracks = {};
    QDir *cd = nullptr;
    //TOOLS-----------------------------------------------------------

    //Shortcuts-------------------------------------------------------
    /*
     * Shortcuts for tracks
        1) delete track Ctrl + D
        2) rename track Ctrl + R

     * Shortcuts for playlists
        1) previuse track ->
        2) play or pause SPACE
        3) next track <-

      * Shortcuts for window of app
        1) Full Window Shift + F
        2) Quit Window Shift + Q
        3) Hide Window Shift + H

      * Shortcuts for move track up or down inside playlist
        1) Move track up
        2) Move track down
    */

    QShortcut *ctrlD = nullptr;
    QShortcut *ctrlR = nullptr;

    QShortcut *previuseSong = nullptr;
    QShortcut *pauseSong = nullptr;
    QShortcut *nextSong = nullptr;

    QShortcut *shiftF = nullptr;
    QShortcut *shiftQ = nullptr;
    QShortcut *shiftH = nullptr;

    QShortcut *moveTrackUp = nullptr;
    QShortcut *moveTrackDown = nullptr;
    //Shortcuts-------------------------------------------------------


    //Own Objects-----------------------------------------------------

    /*
        1) UI own widgets
        2) Managers
        3) System
    */
private:
    // UI own widgets ----------------------------------------------- 1
    //ui widgets
    AddMusicWidget *getAddedTracksFromWidget = nullptr;
    GetStringWidget *getStringFromUserToCreateNewPlaylist = nullptr;
    GetStringWidget *getStringFromUserToRenamePlaylist = nullptr;
    GetStringWidget *getStringFromUserToRenameTrack = nullptr;
    SelectPlaylist *getStringWithSelectedPlaylist = nullptr;
    // UI own widgets ----------------------------------------------- 1

    // Managers ----------------------------------------------------- 2
    ImportManager *importManager = nullptr;
    Playlist *playlistmanager = nullptr;
    Player *playermanager = nullptr;
    // Managers ----------------------------------------------------- 2

    // System ------------------------------------------------------- 3
    System sysmanager;
    // System ------------------------------------------------------- 3
    //Own Objects-----------------------------------------------------


    //default UI
private:
    Ui::Ocean *ui;

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||OBJECTS|||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
};
#endif
