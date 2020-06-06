/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
***Created by bogdyname
*/

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QUrl>
#include <QDir>
#include <QFile>
#include <QList>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QFileDialog>
#include <QMediaObject>
#include <QMediaPlaylist>
#include <QListWidgetItem>
#include <QCoreApplication>

class Playlist : public QMediaPlaylist
{
    Q_OBJECT

    /*
     * Format of playlists = .m3u
     * Dir 'bin' for saving and loading playlists
    */

public:
    Playlist();
    ~Playlist();

    /*-------------------------------------------------------SIGNALS-------------------------------------------------------*/
    /*
        1) set playlist for player class
            1.1) set current playlist
        2) save
            2.1) save current playlist by name and media playlist
            2.2) save selected playlist by name
            2.3) save playlist by name (only name)
        3) rename
            3.1) rename current playlist by name and media playlist
            3.2) rename selected playlist by name
        4) set playlist via Playlist::GetCurrentPlayListName()
        5) create playlist by name
        6) delete playlist by name
        7)
           7.1) add song into playlist from other playlist by index
           7.2) add song into platlist from all songs (default playlist)
    */
signals:
    /*----------------------------------------set playlist player----------------------------------------*/
    void SetCurrentPlayList(QMediaPlaylist *currentPlaylist);
    /*----------------------------------------save------------------------------------------*/
    void CallOutSaveCurrentPlayList(const QString &name, const QStringList &newListOfSongs, QMediaPlaylist *currentPlaylist);
    void CallOutSaveSelectedPlayList(const QString &name, const QStringList &newListOfSongs);
    void CallOutSaveNewPlayList(const QString &name);
    /*----------------------------------------rename----------------------------------------*/
    void CallOutRenameCurrentPlayList(QString &newName, QMediaPlaylist *currentPlaylist);
    void CallOutRenameSelectedPlayList(const QString &newName, const QString &currentName);
    /*----------------------------------------set playlist----------------------------------*/
    void CallOutSetCurrentPlayListName(const QString &nameOfCurrentPlaylist);
    /*----------------------------------------create playlist-------------------------------*/
    void CallOutCreateNewPlayList(const QString &name, const QStringList &tracks);
    /*----------------------------------------delete----------------------------------------*/
    void CallOutRemovePlayListByName(const QString &name);
    /*--------------------------------add song into playlist--------------------------------*/
    void CallOutAddSongIntoPlayList(const QString &song, const QString &nameOfPlayList, const QString &nameOfCurrentPlayList, const unsigned short int &index);
    void CallOutAddSongIntoPlayListFromDefaultPlayList(const QString &song, const QString &nameOfPlayList, const unsigned short int &index);
    /*-------------------------------------------------------SIGNALS-------------------------------------------------------*/


    /*--------------------------------------------------------SLOTS--------------------------------------------------------*/
    /*
        1) save playlist
            1.1) save current playlist
            1.2) save selected playlist
            1.3) save playlist by name (only name)
        2) rename
            2.1) rename current playlist
            2.2) rename selected playlist
        3) set name of playlist
        4) create playlist by name
        5) delete playlist by name
        6) add song into playlist
    */
private slots:
    /*----------------------------------------save------------------------------------------*/
    void SaveCurrentPlayList(const QString &name, const QStringList &newListOfSongs, QMediaPlaylist *currentPlaylist);
    void SaveSelectedPlayList(const QString &name, const QStringList &newListOfSongs);
    void SaveNewPlayList(const QString &name);
    /*----------------------------------------rename----------------------------------------*/
    void RenameCurrentPlayList(const QString &newName, QMediaPlaylist *currentPlaylist);
    void RenameSelectedPlayList(const QString &newName, const QString &currentName);
    /*----------------------------------------set playlist----------------------------------*/
    void SetCurrentPlayListName(const QString &nameOfCurrentPlaylist);
    /*----------------------------------------create playlist-------------------------------*/
    void CreateNewPlayList(const QString &name, const QStringList &tracks);
    /*----------------------------------------delete----------------------------------------*/
    void RemovePlayListByName(const QString &name);
    /*--------------------------------add song into playlist--------------------------------*/
    void AddSongIntoPlayList(const QString &song, const QString &nameOfPlayList, const QString &nameOfCurrentPlayList, const unsigned short int &index);
    void AddSongIntoPlayListFromDefaultPlayList(const QString &song, const QString &nameOfPlayList, const unsigned short int &index);

    /*
        1) set next track
        2) set previuos track
        3) set track by index
    */
public slots:
    void SetNextTrack();
    void SetPreviousTrack();
    void SetTrackByIndex(QListWidgetItem *indexOfTrack);
    /*--------------------------------------------------------SLOTS--------------------------------------------------------*/


    /*----------------------------------------Methods for get data about playlist----------------------------------------*/
    /*
        1) get name of current playlist
        2) get current playlist
        3) load all songs (default playlist)
        4) load playlist by name
        5) get songs from current playlist by name of playlist
        6) Parser for song to get full path of tracks
        7) Parser to remove format and full path
    */
public:
    QString GetCurrentPlayListName(); //--------------------------------------------------------------------------------1) (DONE)
    QMediaPlaylist* GetCurrentPlayList(); //----------------------------------------------------------------------------2) (DONE)
    void LoadPlayList(const QString &name); //--------------------------------------------------------------------------3) (DONE)
    QStringList GetSongsFromCurrentPlayList(const QString &nameOfPlayList); //------------------------------------------4) (DONE)
    const QStringList GetAllTracks();//---------------------------------------------------------------------------------5) (DONE)
    QStringList ParseToGetFullPathOfTracks(const QStringList &list);//--------------------------------------------------6) (DONE)
    QString ParseStringToRemoveFormatAndCurrentPath(const QString &string);//-------------------------------------------7) (DONE)
    /*-----------------------------------------Methods for get data about playlist----------------------------------------*/


    /*----------------------------------------Methods for call it in Private SLOTS----------------------------------------*/
    /*
        1) create playlist by name of new playlist (get it via ui_getstring.h in ocean.cpp) and QFileDialog (pass paths of files in QStringList)
        2) delete playlist by name
        3) load playlist by name
        5) save CURRENT playlist by name and songs inside changed playlist
        6) save playlist by name and songs inside changed playlist
        7) save playlist by name (only name)
        8) rename CURRENT playlist with new name
        9) rename playlist with new name via current name
        10) check if 'bin' dir is exists (else create it!)
       11) add song into playlist
       12) get format of playlist by index
       13) parse string to get format
    */
private:
    bool CreatePlayList(const QString &name, const QStringList &list); //--------------------------------------------------------------------------------------------1) (DONE)
    bool RemovePlayList(const QString &name);//----------------------------------------------------------------------------------------------------------------------2)
    bool LookingForPlayList(const QString &name, QMediaPlaylist *medialist);//---------------------------------------------------------------------------------------3) (DONE)
    bool SavePlaylist(const QString &name, const QStringList &newListOfSongs, QMediaPlaylist *currentPlaylist);//----------------------------------------------------5) (DONE)
    bool SavePlaylist(const QString &name, const QStringList &newListOfSongs);//-------------------------------------------------------------------------------------6) (DONE)
    bool SavePlaylist(const QString &name);//------------------------------------------------------------------------------------------------------------------------7) (DONE)
    bool RenamePlayList(const QString &newName, QMediaPlaylist *currentPlaylist);//----------------------------------------------------------------------------------8)
    bool RenamePlayList(const QString &newName, const QString &currentName); //--------------------------------------------------------------------------------------9)
    bool CheckSettingsDir();//--------------------------------------------------------------------------------------------------------------------------------------10) (DONE)
    bool AddSongIntoPlayListByName(const QString &song, const QString &nameOfPlayList, const QString &nameOfCurrentPlayList, const unsigned short int &index); //---11)
    QString GetFormatOfSong(const QString &nameOfPlayList, const unsigned short int &index); //---------------------------------------------------------------------12) (DONE)
    QString ParseStringToGetFormat(const QString &string);//--------------------------------------------------------------------------------------------------------13) (DONE)
    /*----------------------------------------Methods for call it in Private SLOTS----------------------------------------*/


    /*--------------------------------------------------Objects of class--------------------------------------------------*/
private:
    QDir *cd = nullptr; //---------------------------- works with dir and paths of system
    QStringList allSongs; //----------------------------------- list with paths of all songs
    QString currentPlaylistName; //---------------------------- name of playlist
    QMediaPlaylist *currentPlaylist = nullptr; //-------------- current playlist
    /*--------------------------------------------------Objects of class--------------------------------------------------*/
};

#endif
