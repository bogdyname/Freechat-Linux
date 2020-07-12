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
           6.2) add song into platlist from all songs (default playlist)
        7) move and sort playlist
           7.1) move track to &index by index from current playlist
           7.2) move track to &index by index from playlist by name
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
    void CallOutAddSongIntoPlayList(const QString &song, const QString &nameOfPlayList, const QString &nameOfCurrentPlayList, const unsigned short int &index);
    void CallOutAddSongIntoPlayListFromDefaultPlayList(const QString &song, const QString &nameOfPlayList, const unsigned short int &index);
    /*-------------------------------move song inside playlist------------------------------*/
    void CallOutMoveSongInsideCurrentPlayList(const unsigned short int &currentIndex, const unsigned short int &newIndex);
    void CallOutMoveSongInsidePlayListByName(const unsigned short int &currentIndex, const unsigned short int &newIndex, const QString &name);
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
    void AddSongIntoPlayList(const QString &song, const QString &nameOfPlayList, const QString &nameOfCurrentPlayList, const unsigned short int &index);
    void AddSongIntoPlayListFromDefaultPlayList(const QString &song, const QString &nameOfPlayList, const unsigned short int &index);
    /*-------------------------------move song inside playlist------------------------------*/
    void MoveSongInsideCurrentPlayList(const unsigned short int &currentIndex, const unsigned short int &newIndex);
    void MoveSongInsidePlayListByName(const unsigned short int &currentIndex, const unsigned short int &newIndex, const QString &name);
    /*--------------------------------------------------------SLOTS--------------------------------------------------------*/

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||SIGNALS WITH PRIVATE SLOTS||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/****************************************************************************************************************************************/

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||PUBLIC SLOTS||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

    /*
        1) set next track in current playlist
        2) set previuos track in current playlist
        3) set track by index in current playlist
        4) check default playlist (all songs from 'music' dir)
    */

    /*--------------------------------------------------------SLOTS--------------------------------------------------------*/
public slots:
    void SetNextTrack();
    void SetPreviousTrack();
    void SetTrackByIndex(QListWidgetItem *indexOfTrack);
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
        3) load playlist by name
        4) get songs from current playlist by name of playlist
        5) load all songs (default playlist)
    */

    /*----------------------------------------Methods to get data about playlist----------------------------------------*/
public:
    const QString GetCurrentPlayListName(); //--------------------------------------------------------------------------1)
    QMediaPlaylist* GetCurrentPlayList(); //----------------------------------------------------------------------------2)
    bool LoadPlayList(const QString &name); //--------------------------------------------------------------------------3)
    QStringList GetSongsFromCurrentPlayList(const QString &nameOfPlayList); //------------------------------------------4)
    const QStringList GetAllTracks();//---------------------------------------------------------------------------------5)
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
        1) create playlist by name of new playlist (get it via ui_getstring.h in ocean.cpp) and QFileDialog (pass paths of files in QStringList)
        2) delete playlist by name
        3) load playlist by name
        5) save CURRENT playlist by name and songs inside changed playlist
        6) save playlist by name and songs inside changed playlist
        7) save playlist by name (only name)
        8) rename CURRENT playlist with new name
        9) rename playlist with new name via current name
        10) check if 'bin' dir is exists (else create it!)
        11) add song into playlist by name
        12) remove track by index
        13) remove track by index and name
        14) move track inside playlist by index
        15) move track inside playlist by index and name
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
    bool RemoveTrackByIndex(const int &index); //----------------------------------------------------------------------------------------------------12)
    bool RemoveTrackByIndex(const int &index, const QString &name); //-------------------------------------------------------------------------------13)
    bool RemoveAllTracks();
    bool RemoveAllTracks(const QString &name);
    bool MoveSongInsidePlaylistByIndex(const unsigned short int &currentIndex, const unsigned short int &newIndex); //----------------------------------------------14)
    bool MoveSongInsidePlaylistByIndex(const unsigned short int &currentIndex, const unsigned short int &newIndex, const QString &name); //-------------------------15)
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
        1) parser to get full path of songs
        2) parser to remove full path and format of file (song or playlist [m3u, wav, mp3, m4a])
        3) open file playlist (by name and index)
        4) parse string to get format
    */

public: //using inside Ocean.cpp
    QStringList ParseToGetFullPathOfTracks(const QStringList &list);
    QString ParseStringToRemoveFormatAndCurrentPath(const QString &string);
private: //using inside Playlist.cpp
    QString ParserToGetFormatOfSong(const QString &nameOfPlayList, const unsigned short int &index);
    QString ParseStringToGetFormat(const QString &string);
    /*--------------------------------------------------------PARSERS------------------------------------------------------*/

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*||||||||||||||||||||||||||||||||||||||||||||||||PARSER FOR FORMAT||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/****************************************************************************************************************************************/

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||OBJECTS|||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

private:
    QDir *cd = nullptr; //---------------------------- works with dir and paths of system
    QStringList allSongs; //----------------------------------- list with paths of all songs
    QString currentPlaylistName; //---------------------------- name of playlist
    QMediaPlaylist *currentPlaylist = nullptr; //-------------- current playlist

    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||OBJECTS|||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
    /*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
};

#endif
