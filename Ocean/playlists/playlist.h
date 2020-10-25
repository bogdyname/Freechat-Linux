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
    Q_CLASSINFO("Version", "0.8")

    /*
     * Format of playlists = .m3u8
     * Dir 'bin' for saving and loading playlists
    */

    enum Errors
    {
        ErrorSavePlaylist   = 0,
        ErrorRenamePlaylist = 1,
        ErrorCreatePlaylist = 2,
        ErrorDeletePlaylist = 3,
        ErrorRenameTrack    = 4,
        ErrorDeleteTrack    = 5,
        ErrorAddTrack       = 6
    };

public:
    Playlist(QObject *parent = nullptr);
    ~Playlist();

/****************************************************************************************************************************************/

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||SIGNALS WITH PRIVATE SLOTS||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

    /*
        1) save
            1.1) save current playlist by name and media playlist
            1.2) save selected playlist by name
            1.3) save playlist by name (only name)
        2) rename
            2.1) rename current playlist by name and media playlist
            2.2) rename selected playlist by name
        3) set playlist via Playlist::GetCurrentPlayListName()
        4) create playlist by name
        5) delete playlist and tracks from playlist
           5.1) remove playlist by name
           5.2) remove track from current play list by index
           5.3) remove track by index from playlist by name
           5.4) remove all tracks from current playlist
           5.5) remove all tracks from playlist by name
        6) add songs
           6.1) add song into playlist from other playlist by index
           6.2) add songs into playlist by name via Dragand Drop
           6.3) add songs into current playlist via Drag and Drop
        7) move and sort playlist
           7.1) move track to &index by index from current playlist
           7.2) move track to &index by index from playlist by name
        8) set name of current track
    */

    /*-------------------------------------------------------SIGNALS-------------------------------------------------------*/
signals:
    /*----------------------------------------save------------------------------------------*/
    void CallOutSaveCurrentPlayList(const QString &name, const QStringList &newListOfSongs, QMediaPlaylist *currentPlaylist);
    void CallOutSaveSelectedPlayList(const QString &name, const QStringList &newListOfSongs);
    void CallOutSaveNewPlayList(const QString &name);
    /*----------------------------------------rename----------------------------------------*/
    void CallOutRenameCurrentPlayList(const QString &newName, QMediaPlaylist *currentPlaylist);
    void CallOutRenameSelectedPlayList(const QString &newName, const QString &currentName);
    /*----------------------------------------set playlist----------------------------------*/
    void CallOutSetCurrentPlayListName(const QString &nameOfCurrentPlaylist);
    /*----------------------------------------create playlist-------------------------------*/
    void CallOutCreateNewPlayList(const QString &name, const QStringList &tracks);
    /*----------------------------------------delete----------------------------------------*/
    void CallOutRemovePlayListByName(const QString &name);
    void CallOutRemoveTrackFromCurrentPlayListByIndex(const int &indexOfTrack);
    void CallOutRemoveTrackFromPlayListByIndex(const int &indexOfTrack, const QString &name);
    void CallOutRemoveAllTracksFromCurrentPlayList();
    void CallOutRemoveAllTracksFromPlayListByName(const QString &name);
    /*--------------------------------add song into playlist--------------------------------*/
    void CallOutAddSongIntoPlayList(const QString &song, const QString &nameOfPlayList, const QString &nameOfCurrentPlayList, const int &index);
    void CallOutAddSongsIntoPlaylistByNameViaDragAndDrop(const QStringList &songs, const QString &nameOfPlayList);
    void CallOutAddSongsIntoCurrentPlaylistViaDragAndDrop(const QStringList &songs);
    /*-------------------------------move song inside playlist------------------------------*/
    void CallOutMoveSongInsideCurrentPlayList(const int &currentIndex, const int &newIndex);
    void CallOutMoveSongInsidePlayListByName(const int &currentIndex, const int &newIndex, const QString &name);
    /*-------------------------------set name of current track------------------------------*/
    void CallOutSetNameOfCurrentTrack(const QString &name);
    /*---------------------------set image of current playback mode-------------------------*/
    void CallOutSetImageOfCurrentPlaybackMode(const int &counter);
    /*------------------------------------Rename name of track------------------------------*/
    void CallOutRenameTrackByIndex(const int &index, const QString &playlist, const QString &newName);
    /*---------------------------------------Clear all songs--------------------------------*/
    void CallOutClearAllSongs();
    /*---------------------------------------Clear one song---------------------------------*/
    void CallOutClearOneSong(const int &index);
    /*---------------------------------------Error Message----------------------------------*/
    void CallOutErrorMessage(const int &error);
    /*-------------------------------------------------------SIGNALS-------------------------------------------------------*/


    /*--------------------------------------------------------SLOTS--------------------------------------------------------*/
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
    void RemoveTrackFromCurrentPlayListByIndex(const int &indexOfTrack);
    void RemoveTrackFromPlayListByIndex(const int &indexOfTrack, const QString &name);
    void RemoveAllTracksFromCurrentPlayList();
    void RemoveAllTracksFromPlayListByName(const QString &name);
    /*--------------------------------add song into playlist--------------------------------*/
    void AddSongIntoPlayList(const QString &song, const QString &nameOfPlayList, const QString &nameOfCurrentPlayList, const int &index);
    void AddSongsIntoPlaylistByNameViaDragAndDrop(const QStringList &songs, const QString &nameOfPlayList);
    void AddSongsIntoCurrentPlaylistViaDragAndDrop(const QStringList &songs);
    /*-------------------------------move song inside playlist------------------------------*/
    void MoveSongInsideCurrentPlayList(const int &currentIndex, const int &newIndex);
    void MoveSongInsidePlayListByName(const int &currentIndex, const int &newIndex, const QString &name);
    /*-------------------------------set name of current track------------------------------*/
    void SetNameOfCurrentTrack(int index);
    /*------------------------------------Rename name of track------------------------------*/
    void RenameTrackByIndex(const int &index, const QString &playlist, const QString &newName);
    /*---------------------------------------Clear all songs--------------------------------*/
    void ClearAllSongs();
    /*---------------------------------------Clear one song---------------------------------*/
    void ClearOneSong(const int &index);
    /*--------------------------------------------------------SLOTS--------------------------------------------------------*/

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||SIGNALS WITH PRIVATE SLOTS||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/****************************************************************************************************************************************/

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||PUBLIC SLOTS||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

    /*
        1) set mode of playback
        2) set next track in current playlist
        3) set previuos track in current playlist
        4) set track by index in current playlist
        5) check default playlist (all songs from 'music' dir)
    */

    /*--------------------------------------------------------SLOTS--------------------------------------------------------*/
public slots:
    void SetModOfPlayback();
    void SetNextTrack();
    void SetPreviousTrack();
    void SetTrackByIndex(const int &indexOfTrack);
    void CheckDefaultPlayList();
    /*--------------------------------------------------------SLOTS--------------------------------------------------------*/

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||PUBLIC SLOTS||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/****************************************************************************************************************************************/

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||METHODS TO GET DATA ABOUT PLAYLIST||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

    /*
        1) get name of current playlist
        2) get current playlist
        3) get current index
        4) load playlist by name
        5) get songs from current playlist by name of playlist
        6) load all songs (default playlist)
        7) get all playlists
    */

    /*----------------------------------------Methods to get data about playlist----------------------------------------*/
public:
    const QString GetCurrentPlayListName(); //--------------------------------------------------------------------------1)
    QMediaPlaylist* GetCurrentPlayList(); //----------------------------------------------------------------------------2)
    int GetCurrentIndex(); //-------------------------------------------------------------------------------------------3)
    bool LoadPlayList(const QString &name); //--------------------------------------------------------------------------4)
    QStringList GetSongsFromCurrentPlayList(const QString &nameOfPlayList); //------------------------------------------5)
    const QStringList GetAllTracks(); //--------------------------------------------------------------------------------6)
    const QStringList GetAllPlaylists(); //-----------------------------------------------------------------------------7)
    /*-----------------------------------------Methods to get data about playlist----------------------------------------*/

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||METHODS TO GET DATA ABOUT PLAYLIST||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/****************************************************************************************************************************************/

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*||||||||||||||||||||||||||||||||||||||||METHODS TO CALL IN PRIVATE SLOTS|||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

    /*----------------------------------------Methods to call it in Private SLOTS----------------------------------------*/
    /*
        --create
        1) create playlist by name of new playlist (get it via ui_getstring.h in ocean.cpp) and QFileDialog (pass paths of files in QStringList)
        --delete
        2) delete playlist by name
        --load
        3) load playlist by name
        --save
        4) save CURRENT playlist by name and songs inside changed playlist
        5) save playlist by name and songs inside changed playlist
        6) save playlist by name (only name)
        --rename
        7) rename CURRENT playlist with new name
        8) rename playlist with new name via current name
        --settings
        9) check if 'bin' dir is exists (else create it!)
        --add track into playlist
        10) add song into playlist by name
        11) add songs into playlist by name via drag and drop
        12) add songs into current playlist via drag and drop
        --remove
        13) remove track by index
        14) remove track by index from app
        15) remove track by index and name
        16) remove all tracks from playlist
        17) remove all tracks from app
        18) remove all track from playlist by name
        --move
        19) move track inside playlist by index
        20) move track inside playlist by index and name
        --rename track
        19) rename track by indexex
        21) rename track by indexex
    */
private:
    bool CreatePlayList(const QString &name, const QStringList &list); //--------------------------------------------------------------------------------------------1) (DONE)
    bool RemovePlayList(const QString &name);//----------------------------------------------------------------------------------------------------------------------2) (DONE)
    bool LookingForPlayList(const QString &name, QMediaPlaylist *medialist);//---------------------------------------------------------------------------------------3) (DONE)
    bool SavePlaylist(const QString &name, const QStringList &newListOfSongs, QMediaPlaylist *currentPlaylist);//----------------------------------------------------4) (DONE)
    bool SavePlaylist(const QString &name, const QStringList &newListOfSongs);//-------------------------------------------------------------------------------------5) (DONE)
    bool SavePlaylist(const QString &name);//------------------------------------------------------------------------------------------------------------------------6) (DONE)
    bool RenamePlayList(const QString &newName, QMediaPlaylist *currentPlaylist);//----------------------------------------------------------------------------------7) (DONE)
    bool RenamePlayList(const QString &newName, const QString &currentName); //--------------------------------------------------------------------------------------8) (DONE)
    bool CheckSettingsDir();//---------------------------------------------------------------------------------------------------------------------------------------9) (DONE)
    bool AddSongIntoPlayListByName(const QString &song, const QString &nameOfPlayList, const QString &nameOfCurrentPlayList, const int &index); //------------------10) (DONE)
    bool AddSongsIntoPlayListByName(const QStringList &songs, const QString &nameOfPlayList);//---------------------------------------------------------------------11) (DONE)
    bool AddSongsIntoCurrentPlayList(const QStringList &songs);//---------------------------------------------------------------------------------------------------12) (DONE)
    bool RemoveTrackByIndex(const int &index); //-------------------------------------------------------------------------------------------------------------------13) (DONE)
    bool RemoveTrackByIndexFromApp(const int &index); //------------------------------------------------------------------------------------------------------------14) (DONE)
    bool RemoveTrackByIndex(const int &index, const QString &name); //----------------------------------------------------------------------------------------------15) (DONE)
    bool RemoveAllTracks(); //--------------------------------------------------------------------------------------------------------------------------------------16) (DONE)
    bool RemoveAllTracksFromApp(); //-------------------------------------------------------------------------------------------------------------------------------17) (DONE)
    bool RemoveAllTracks(const QString &name); //-------------------------------------------------------------------------------------------------------------------18) (DONE)
    bool MoveSongInsidePlaylistByIndex(const int &currentIndex, const int &newIndex); //----------------------------------------------------------------------------19)
    bool MoveSongInsidePlaylistByIndex(const int &currentIndex, const int &newIndex, const QString &name); //-------------------------------------------------------20)
    bool RenameTrack(const int &index, const QString &playlist, const QString &newName); //-------------------------------------------------------------------------21) (DONE)
    /*----------------------------------------Methods to call it in Private SLOTS----------------------------------------*/

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*||||||||||||||||||||||||||||||||||||||||METHODS TO CALL IN PRIVATE SLOTS|||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/****************************************************************************************************************************************/

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*||||||||||||||||||||||||||||||||||||||||||||||||PARSER FOR FORMAT||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

    /*--------------------------------------------------------PARSERS------------------------------------------------------*/
    /*
        1) parser to get name from file by index
        2) parser to get full path of songs
        3) parser to remove full path and format of file (song or playlist [m3u, wav, mp3, m4a])
        4) open file playlist (by name and index)
        5) parse string to get format
        6) parse full path to rename track
    */

public: //using inside Ocean.cpp
    QString ParserToGetNameOfSongByIndex(const int &index);
    QStringList ParseToGetFullPathOfTracks(const QStringList &list);
    QString ParseStringToRemoveFormatAndCurrentPath(const QString &string);
        //using inside Playlist.cpp and Ocean.cpp
    QString ParserToGetFormatOfSong(const QString &nameOfPlayList, const int &index);
    QString ParseStringToGetFormat(const QString &string);
    QString ParseToGetCurrentName(const QString &fullPath);
    /*--------------------------------------------------------PARSERS------------------------------------------------------*/

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*||||||||||||||||||||||||||||||||||||||||||||||||PARSER FOR FORMAT||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/****************************************************************************************************************************************/

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||OBJECTS|||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

private:
    int counterOfPlayback;
    QDir *cd = nullptr; //------------------------------------- works with dir and paths of system
    QStringList allSongs; //----------------------------------- list with paths of all songs
    QString currentPlaylistName; //---------------------------- name of playlist
    QMediaPlaylist *currentPlaylist = nullptr; //-------------- current playlist

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||OBJECTS|||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
};

#endif
