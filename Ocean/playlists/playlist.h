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
#include <QStringList>
#include <QFileDialog>
#include <QMediaObject>
#include <QMediaPlaylist>
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
            1.2) set default playlist (playlist with all songs)
        2) save
            2.1) save current playlist by name and media playlist
            2.2) save selected playlist by name
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
    void SetDefaultPlayList(QMediaPlaylist *defaultPlaylist);
    /*----------------------------------------save------------------------------------------*/
    void CallOutSaveCurrentPlayList(const QString &name, const QStringList &newListOfSongs, QMediaPlaylist *currentPlaylist);//---------TTS
    void CallOutSaveSelectedPlayList(const QString &name, const QStringList &newListOfSongs);//-----------------------------------------TTS
    /*----------------------------------------rename----------------------------------------*/
    void CallOutRenameCurrentPlayList(QString &newName, QMediaPlaylist *currentPlaylist);//---------------------------------------------TTS
    void CallOutRenameSelectedPlayList(const QString &newName, const QString &currentName);//-------------------------------------------TTS
    /*----------------------------------------set playlist----------------------------------*/
    void CallOutSetCurrentPlayListName(const QString &nameOfCurrentPlaylist);
    /*----------------------------------------create playlist-------------------------------*/
    void CallOutCreateNewPlayList(const QString &name);//-------------------------------------------------------------------------------TTS
    /*----------------------------------------delete----------------------------------------*/
    void CallOutRemovePlayListByName(const QString &name);//----------------------------------------------------------------------------TTS
    /*--------------------------------add song into playlist--------------------------------*/
    void CallOutAddSongIntoPlayList(const QString &song, const QString &nameOfPlayList, const QString &nameOfCurrentPlayList, const unsigned short int &index);//TTS
    void CallOutAddSongIntoPlayListFromDefaultPlayList(const QString &song, const QString &nameOfPlayList, const unsigned short int &index);//TTS
    /*-------------------------------------------------------SIGNALS-------------------------------------------------------*/


    /*--------------------------------------------------------SLOTS--------------------------------------------------------*/
    /*
        1) save playlist
            1.1) save current playlist
            1.2) save selected playlist
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
    /*----------------------------------------rename----------------------------------------*/
    void RenameCurrentPlayList(const QString &newName, QMediaPlaylist *currentPlaylist);
    void RenameSelectedPlayList(const QString &newName, const QString &currentName);
    /*----------------------------------------set playlist----------------------------------*/
    void SetCurrentPlayListName(const QString &nameOfCurrentPlaylist);
    /*----------------------------------------create playlist-------------------------------*/
    void CreateNewPlayList(const QString &name);
    /*----------------------------------------delete----------------------------------------*/
    void RemovePlayListByName(const QString &name);
    /*--------------------------------add song into playlist--------------------------------*/
    void AddSongIntoPlayList(const QString &song, const QString &nameOfPlayList, const QString &nameOfCurrentPlayList, const unsigned short int &index);
    void AddSongIntoPlayListFromDefaultPlayList(const QString &song, const QString &nameOfPlayList, const unsigned short int &index);
    /*--------------------------------------------------------SLOTS--------------------------------------------------------*/


    /*----------------------------------------Methods for get data about playlist----------------------------------------*/
    /*
        1) get name of current playlist
        2) get current playlist
        3) get default playlist
        4) load all songs (default playlist)
        5) load playlist by name
        6) get songs from current playlist by name of playlist
        7) get all songs (default playlist)
    */
public:
    QString GetCurrentPlayListName(); //--------------------------------------------------------------------------------1)
    QMediaPlaylist* GetCurrentPlayList(); //----------------------------------------------------------------------------2)
    QMediaPlaylist* GetDefaultPlayList(); //----------------------------------------------------------------------------3)
    void LoadDefaultPlayList(); //--------------------------------------------------------------------------------------4)
    void LoadPlayList(const QString &name); //--------------------------------------------------------------------------5)
    QStringList GetSongsFromCurrentPlayList(const QString &nameOfPlayList); //------------------------------------------6)
    QStringList GetSongsFromDeaultPlayList(); //------------------------------------------------------------------------7)
    /*----------------------------------------Methods for get data about playlist----------------------------------------*/


    /*----------------------------------------Methods for call it in Private SLOTS----------------------------------------*/
    /*
        1) create playlist by name of new playlist (get it via ui_getstring.h in ocean.cpp) and QFileDialog (pass paths of files in QStringList)
        2) delete playlist by name
        3) load playlist by name
        4) load default playlist (all songs)
        5) save CURRENT playlist by name and songs inside changed playlist
        6) save playlist by name and songs inside changed playlist
        7) rename CURRENT playlist with new name
        8) rename playlist with new name via current name
        9) check if 'bin' dir is exists (else create it!)
       10) add song into playlist
       11) get format of playlist by index
       12) parse string to get format
    */
private:
    bool CreatePlayList(const QString &name, const QStringList &list); //--------------------------------------------------1)
    bool RemovePlayList(const QString &name);//----------------------------------------------------------------------------2)
    bool LookingForPlayList(const QString &name, QMediaPlaylist *medialist);//---------------------------------------------3)
    bool CreateDefaultPlaylist(QMediaPlaylist *medialist);//---------------------------------------------------------------4)
    bool SavePlaylist(const QString &name, const QStringList &newListOfSongs, QMediaPlaylist *currentPlaylist);//----------5)
    bool SavePlaylist(const QString &name, const QStringList &newListOfSongs);//-------------------------------------------6)
    bool RenamePlayList(const QString &newName, QMediaPlaylist *currentPlaylist);//----------------------------------------7)
    bool RenamePlayList(const QString &newName, const QString &currentName); //--------------------------------------------8)
    bool CheckSettingsDir();//---------------------------------------------------------------------------------------------9)
    bool AddSongIntoPlayListByName(const QString &song, const QString &nameOfPlayList, const QString &nameOfCurrentPlayList, const unsigned short int &index); //---10)
    QString GetFormatOfSong(const QString &nameOfPlayList, const unsigned short int &index); //------11)
    QString ParseStringToGetFormat(const QString &string);
    /*----------------------------------------Methods for call it in Private SLOTS----------------------------------------*/


    /*--------------------------------------------------Objects of class--------------------------------------------------*/
private:
    QFileDialog *dialog = nullptr; //-------------------------- to open file dialog of system to get files
    QDir *settingsDir = nullptr; //---------------------------- works with dir and paths of system
    QStringList allSongs; //----------------------------------- list with paths of all songs
    QString currentPlaylistName; //---------------------------- name of playlist
    QMediaPlaylist *currentPlaylist = nullptr; //-------------- current playlist
    QMediaPlaylist *defaultPlaylist = nullptr; //-------------- plsylist for all songs (default playlist)
    /*--------------------------------------------------Objects of class--------------------------------------------------*/
};

#endif
