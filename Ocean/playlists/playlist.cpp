/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
***Created by bogdyname
*/

#include "playlist.h"
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||MAIN|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
Playlist::Playlist(QObject *parent)
    : QMediaPlaylist(parent)
{
    try
    {
        cd = new QDir();
        currentPlaylist = new QMediaPlaylist(this);
    }
    catch(std::bad_alloc &exp)
    {
        qCritical() << "Exception caught: " << exp.std::bad_alloc::what();
        exit(1);
    }
    catch(...)
    {
        qCritical() << "Some exception caught";
        exit(1);
    }

    //setting up variable to switch status of playback
    //(Sequential (-1), Loop(0), CurrentItemInLoop(1), Random(2))
    counterOfPlayback = -1;

    this->CheckDefaultPlayList();

    //For bin folder
    cd->setCurrent(QCoreApplication::applicationDirPath());

    //Check folder of settings/playlist
    if(cd->mkdir("bin"))
        qDebug() << "Folder 'bin' created";
    else
        qDebug() << "Folder 'bin' already exists!";

    //Setting up of media playlist object
    //default playback mode
    currentPlaylist->setPlaybackMode(QMediaPlaylist::Sequential);

    /*---------------------------------signals with slots---------------------------------*/
    /*
     * Save ---------------------------
        1.1) save current playlist
        1.2) save selected playlist
        1.3) save playlist by name
     * Rename -------------------------
        2.1) rename current playlist
        2.2) rename selected playlist
     * Name ---------------------------
        3.1) set name of current playlist (playlist 'all' too!)
     * Create -------------------------
        4.1) create new playlist
     * Remove -------------------------
        5.1) remove playlist by name
        5.2) remove track by index from current playlist
        5.3) remove track by index from &name
     * Add ----------------------------
        6.1) add song into playlist by index
     * Move ---------------------------
       7.1) move track to &index by index from current playlist
       7.2) move track to &index by index from playlist by name
     * Rename track -------------------
       8.1) rename track by index
     * Remove tracks ------------------
       9.1) remove all tracks
       9.2) remove one track
    */
    //Save
    connect(this, &Playlist::CallOutSaveCurrentPlayList, this, &Playlist::SaveCurrentPlayList);
    connect(this, &Playlist::CallOutSaveSelectedPlayList, this, &Playlist::SaveSelectedPlayList);
    connect(this, &Playlist::CallOutSaveNewPlayList, this, &Playlist::SaveNewPlayList);
    //Rename
    connect(this, &Playlist::CallOutRenameCurrentPlayList, this, &Playlist::RenameCurrentPlayList);
    connect(this, &Playlist::CallOutRenameSelectedPlayList, this, &Playlist::RenameSelectedPlayList);
    //Name
    connect(this, &Playlist::CallOutSetCurrentPlayListName, this, &Playlist::SetCurrentPlayListName);
    //Create
    connect(this, &Playlist::CallOutCreateNewPlayList, this, &Playlist::CreateNewPlayList);
    //Remove
    connect(this, &Playlist::CallOutRemovePlayListByName, this, &Playlist::RemovePlayListByName);
    connect(this, &Playlist::CallOutRemoveTrackFromCurrentPlayListByIndex, this, &Playlist::RemoveTrackFromCurrentPlayListByIndex);
    connect(this, &Playlist::CallOutRemoveTrackFromPlayListByIndex, this, &Playlist::RemoveTrackFromPlayListByIndex);
    connect(this, &Playlist::CallOutRemoveAllTracksFromCurrentPlayList, this, &Playlist::RemoveAllTracksFromCurrentPlayList);
    connect(this, &Playlist::CallOutRemoveAllTracksFromPlayListByName, this, &Playlist::RemoveAllTracksFromPlayListByName);
    //Add song
    connect(this, &Playlist::CallOutAddSongIntoPlayList, this, &Playlist::AddSongIntoPlayList);
    connect(this, &Playlist::CallOutAddSongsIntoPlaylistByNameViaDragAndDrop, this, &Playlist::AddSongsIntoPlaylistByNameViaDragAndDrop);
    connect(this, &Playlist::CallOutAddSongsIntoCurrentPlaylistViaDragAndDrop, this, &Playlist::AddSongsIntoCurrentPlaylistViaDragAndDrop);
    //Move song
    connect(this, &Playlist::CallOutMoveSongInsideCurrentPlayList, this, &Playlist::MoveSongInsideCurrentPlayList);
    connect(this, &Playlist::CallOutMoveSongInsidePlayListByName, this, &Playlist::MoveSongInsidePlayListByName);
    //Set name of current track
    connect(currentPlaylist, &QMediaPlaylist::currentIndexChanged, this, &Playlist::SetNameOfCurrentTrack);
    //Rename track
    connect(this, &Playlist::CallOutRenameTrackByIndex, this, &Playlist::RenameTrackByIndex);
    //Clear all songs
    connect(this, &Playlist::CallOutClearAllSongs, this, &Playlist::ClearAllSongs);
    //Clear one song
    connect(this, &Playlist::CallOutClearOneSong, this, &Playlist::ClearOneSong);

    return;
}

Playlist::~Playlist()
{
    delete cd;

    qDebug() << "Destructor from Playlist.cpp";
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||MAIN|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||SLOTS PRIVATE||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------SAVE METHODS---------------------------------------*/
void Playlist::SaveCurrentPlayList(const QString &name, const QStringList &newListOfSongs, QMediaPlaylist *currentPlaylist)
{
    if(name == "" && newListOfSongs.isEmpty())
        return;

    if(!this->SavePlaylist(name, newListOfSongs, currentPlaylist))
        emit this->CallOutErrorMessage(ErrorSavePlaylist);

    return;
}

void Playlist::SaveSelectedPlayList(const QString &name, const QStringList &newListOfSongs)
{
    if(name == "" && newListOfSongs.isEmpty())
        return;

    if(this->SavePlaylist(name, newListOfSongs))
        emit this->CallOutErrorMessage(ErrorSavePlaylist);

    return;
}

void Playlist::SaveNewPlayList(const QString &name)
{
    if(name == "")
        return;

    if(!this->SavePlaylist(name))
        emit this->CallOutErrorMessage(ErrorSavePlaylist);

    return;
}
/*---------------------------------------SAVE METHODS---------------------------------------*/


/*--------------------------------------RENAME METHODS--------------------------------------*/
void Playlist::RenameCurrentPlayList(const QString &newName, QMediaPlaylist *currentPlaylist)
{
    if(newName == "")
        return;

    if(!this->RenamePlayList(newName, currentPlaylist))
        emit this->CallOutErrorMessage(ErrorRenamePlaylist);

    return;
}

void Playlist::RenameSelectedPlayList(const QString &newName, const QString &currentName)
{
    if((newName == "") && (currentName == ""))
        return;

    if(!this->RenamePlayList(newName, currentName))
        emit this->CallOutErrorMessage(ErrorRenamePlaylist);

    return;
}
/*--------------------------------------RENAME METHODS--------------------------------------*/


/*----------------------------------------SETTINGS METHODS------------------------------------*/
void Playlist::SetCurrentPlayListName(const QString &nameOfCurrentPlaylist)
{
    currentPlaylistName.clear();
    currentPlaylistName += nameOfCurrentPlaylist;

    return;
}
/*----------------------------------------SETTINGS METHODS------------------------------------*/


/*----------------------------------------CREATE METHODS--------------------------------------*/
void Playlist::CreateNewPlayList(const QString &name, const QStringList &tracks)
{
    if(name == "")
        return;

    if(!this->CreatePlayList(name, tracks))
        emit this->CallOutErrorMessage(ErrorCreatePlaylist);

    return;
}
/*----------------------------------------CREATE METHODS--------------------------------------*/


/*----------------------------------------DELETE METHODS--------------------------------------*/
void Playlist::RemovePlayListByName(const QString &name)
{
    if(name == "")
        return;

    if(!this->RemovePlayList(name))
        emit this->CallOutErrorMessage(ErrorDeletePlaylist);

    return;
}
/*----------------------------------------DELETE METHODS--------------------------------------*/


/*--------------------------------------REMOVE METHODS--------------------------------------*/
void Playlist::RemoveTrackFromCurrentPlayListByIndex(const int &indexOfTrack)
{
    if(!this->RemoveTrackByIndex(indexOfTrack))
        emit this->CallOutErrorMessage(ErrorDeleteTrack);

    return;
}

void Playlist::RemoveTrackFromPlayListByIndex(const int &indexOfTrack, const QString &name)
{
    if(name == "")
        return;

    if(name != "all")
    {
        if(!this->RemoveTrackByIndex(indexOfTrack, name))
            emit this->CallOutErrorMessage(ErrorDeleteTrack);
    }
    else
    {
        if(!this->RemoveTrackByIndexFromApp(indexOfTrack))
            emit this->CallOutErrorMessage(ErrorDeleteTrack);
    }

    return;
}

void Playlist::RemoveAllTracksFromCurrentPlayList()
{
    if(!this->RemoveAllTracks())
        emit this->CallOutErrorMessage(ErrorDeleteTrack);

    return;
}

void Playlist::RemoveAllTracksFromPlayListByName(const QString &name)
{
    if(name == "")
        return;

    if(name != "all")
    {
        if(!this->RemoveAllTracks(name))
            emit this->CallOutErrorMessage(ErrorDeleteTrack);
    }
    else
    {
        if(!this->RemoveAllTracksFromApp())
            emit this->CallOutErrorMessage(ErrorDeleteTrack);
    }

    return;
}
/*--------------------------------------REMOVE METHODS--------------------------------------*/


/*------------------------------------------ADD METHODS--------------------------------------*/
void Playlist::AddSongIntoPlayList(const QString &song, const QString &nameOfPlayList, const QString &nameOfCurrentPlayList, const int &index)
{
    if(!this->AddSongIntoPlayListByName(song, nameOfPlayList, nameOfCurrentPlayList, index))
        emit this->CallOutErrorMessage(ErrorAddTrack);

    return;
}

void Playlist::AddSongsIntoPlaylistByNameViaDragAndDrop(const QStringList &songs, const QString &nameOfPlayList)
{
    if(!this->AddSongsIntoPlayListByName(songs, nameOfPlayList))
        emit this->CallOutErrorMessage(ErrorAddTrack);

    return;
}

void Playlist::AddSongsIntoCurrentPlaylistViaDragAndDrop(const QStringList &songs)
{
    if(!this->AddSongsIntoCurrentPlayList(songs))
        emit this->CallOutErrorMessage(ErrorAddTrack);

    return;
}
/*------------------------------------------ADD METHODS--------------------------------------*/


/*---------------------------------------MOVE METHODS---------------------------------------*/
void Playlist::MoveSongInsideCurrentPlayList(const int &currentIndex, const int &newIndex)
{
    if(MoveSongInsidePlaylistByIndex(currentIndex, newIndex))
        qDebug() << "track is moved into " << newIndex << "from " << currentIndex;
    else
        qCritical() << "error: can't move track into new index";

    return;
}

void Playlist::MoveSongInsidePlayListByName(const int &currentIndex, const int &newIndex, const QString &name)
{
    if(name == "")
        return;

    if(MoveSongInsidePlaylistByIndex(currentIndex, newIndex, name))
        qDebug() << "track is moved into " << newIndex << "from " << currentIndex;
    else
        qCritical() << "error: can't move track into new index";

    return;
}
/*---------------------------------------MOVE METHODS---------------------------------------*/

/*-----------------------------------------SET NAME-----------------------------------------*/
void Playlist::SetNameOfCurrentTrack(int index)
{
    if(index == -1)
        return;
    else
        emit this->CallOutSetNameOfCurrentTrack(ParserToGetNameOfSongByIndex(index));

    return;
}
/*-----------------------------------------SET NAME-----------------------------------------*/

/*--------------------------------------RENAME NAME OF TRACK--------------------------------*/
void Playlist::RenameTrackByIndex(const int &index, const QString &playlist, const QString &newName)
{
    if(playlist == "")
        return;

    if(!this->RenameTrack(index, playlist, newName))
        emit this->CallOutErrorMessage(ErrorRenameTrack);

    return;
}
/*--------------------------------------RENAME NAME OF TRACK--------------------------------*/

/*-------------------------------------------CLEAR SONGS------------------------------------*/
void Playlist::ClearAllSongs()
{
    //clear all buffer
    allSongs.clear();

    return;
}

void Playlist::ClearOneSong(const int &index)
{
    //clear track at index buffer
    allSongs.removeAt(index);

    return;
}
/*-------------------------------------------CLEAR SONGS------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||SLOTS PRIVATE||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||SLOTS PUBLIC|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
void Playlist::SetModOfPlayback()
{
    //Current state of playback
    counterOfPlayback == 2 ? counterOfPlayback = -1 : ++counterOfPlayback ;

    switch(counterOfPlayback)
    {
        //Loop all tracks
        case 0:
        {
            currentPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
            emit this->CallOutSetImageOfCurrentPlaybackMode(0);
        }
        break;

        //Current track in loop
        case 1:
        {
            currentPlaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
            emit this->CallOutSetImageOfCurrentPlaybackMode(1);
        }
        break;

        //Random tracks
        case 2:
        {
            currentPlaylist->setPlaybackMode(QMediaPlaylist::Random);
            emit this->CallOutSetImageOfCurrentPlaybackMode(2);
        }
        break;

        //Default sequential player (one by one)
        default:
        {
            currentPlaylist->setPlaybackMode(QMediaPlaylist::Sequential);
            emit this->CallOutSetImageOfCurrentPlaybackMode(-1);
        }
        break;
    }

    return;
}

void Playlist::SetNextTrack()
{
    currentPlaylist->next();

    return;
}

void Playlist::SetPreviousTrack()
{
    currentPlaylist->previous();

    return;
}

void Playlist::SetTrackByIndex(const int &indexOfTrack)
{
    currentPlaylist->setCurrentIndex(indexOfTrack);

    return;
}

void Playlist::CheckDefaultPlayList()
{
    //Check default playlist
    if(!QFile::exists(QCoreApplication::applicationDirPath() + "/bin/all.m3u8"))
    {
        //Create playlist with all songs
        //For get all songs into 'allSongs' variable
        cd->setCurrent(QCoreApplication::applicationDirPath() + "/music/");
        allSongs = cd->entryList(QStringList() << "*.mp3" << "*.MP3" << "*.wav" << "*.WAV", QDir::Files);

        QMediaPlaylist *buffer = new QMediaPlaylist();

        //add song into playlist
        for(const QString &iter : allSongs)
            buffer->addMedia(QMediaContent(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/music/" + iter)));

        //Save main playlist
        buffer->save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/all.m3u8"), "m3u8");

        //Clear memory
        delete buffer;
    }
    else
    {
        //Reboot songs inside playlist with all songs
        //For get all songs into 'allSongs' variable
        cd->setCurrent(QCoreApplication::applicationDirPath() + "/music/");
        allSongs = cd->entryList(QStringList() << "*.mp3" << "*.MP3" << "*.wav" << "*.WAV" << "*.m4a" << "*.M4A", QDir::Files);

        QMediaPlaylist *buffer = new QMediaPlaylist();

        //Clear current file to add new files
        buffer->load(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/all.m3u8"), "m3u8");
        buffer->clear();

        //add song into playlist
        for(const QString &iter : allSongs)
            buffer->addMedia(QMediaContent(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/music/" + iter)));

        //Save main playlist
        buffer->save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/all.m3u8"), "m3u8");

        //Clear memory
        delete buffer;
    }

    return;
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||SLOTS PUBLIC|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||METHODS PUBLIC|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
const QString Playlist::GetCurrentPlayListName()
{
    return currentPlaylistName;
}

QMediaPlaylist* Playlist::GetCurrentPlayList()
{
    return currentPlaylist;
}

int Playlist::GetCurrentIndex()
{
    return currentPlaylist->currentIndex();
}

bool Playlist::LoadPlayList(const QString &name)
{
    if(LookingForPlayList(name, currentPlaylist))
        return true;
    else
        return false;
}

QStringList Playlist::GetSongsFromCurrentPlayList(const QString &nameOfPlayList)
{
    QStringList songs = {};

    if((nameOfPlayList == "") && (CheckSettingsDir() == false))
        return songs;

    //path to file
    const QString path = QCoreApplication::applicationDirPath() + "/bin/" + nameOfPlayList + ".m3u8";

    QFile file;
    file.setFileName(path);

    if(file.exists())
    {
        if(!file.open(QFile::ReadOnly))
            //Return empty list of songs
            return songs;
        else
        {
            QTextStream stream(&file);

            //Write paths of files (paths of songs) into list buffer line by line from file
            while(!stream.atEnd())
                songs.push_back(stream.readLine());

            file.close();
        }
    }
    else
        //If playlist file not exists return empty list of songs
        return songs;

    //return list with songs
    return songs;
}

const QStringList Playlist::GetAllTracks()
{
    return allSongs;
}

const QStringList Playlist::GetAllPlaylists()
{
    cd->setCurrent(QCoreApplication::applicationDirPath() + "/bin/");
    QStringList playlists = cd->entryList(QStringList() << "*.m3u8" << "*.M3U8", QDir::Files);
    cd->setCurrent(QCoreApplication::applicationDirPath());

    return playlists;
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||METHODS PUBLIC|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||METHODS PRIVATE||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------CREATE METHODS--------------------------------------*/
bool Playlist::CreatePlayList(const QString &name, const QStringList &list)
{
    if(name == "")
        return false;

    CheckSettingsDir();
    cd->setCurrent(QCoreApplication::applicationDirPath());

    QMediaPlaylist *bufferPlaylist = new QMediaPlaylist();

    //add song into playlist
    for(const QString &iter : list)
        bufferPlaylist->addMedia(QMediaContent(QUrl::fromLocalFile(iter)));

    //Save created playlist
    if(bufferPlaylist->save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + name + ".m3u8"), "m3u8"))
    {
        delete bufferPlaylist;
        return true;
    }
    else
    {
        delete bufferPlaylist;
        return false;
    }
}
/*----------------------------------------CREATE METHODS--------------------------------------*/


/*----------------------------------------DELETE METHODS--------------------------------------*/
bool Playlist::RemovePlayList(const QString &name)
{
    if(name == "")
        return false;

    CheckSettingsDir();

    QFile buffer(QCoreApplication::applicationDirPath() + "/bin/" + name + ".m3u8");

    if(buffer.remove())
        return true;
    else
        return false;
}
/*----------------------------------------DELETE METHODS--------------------------------------*/


/*----------------------------------------LOAD METHODS---------------------------------------*/
bool Playlist::LookingForPlayList(const QString &name, QMediaPlaylist *medialist)
{
    if(name == "")
        return false;

    CheckSettingsDir();

    medialist->load(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + name + ".m3u8"), "m3u8");
    medialist->setCurrentIndex(0);

    if(!medialist->isEmpty())
        return true;
    else
        return false;
}
/*----------------------------------------LOAD METHODS---------------------------------------*/


/*---------------------------------------SAVE METHODS---------------------------------------*/
bool Playlist::SavePlaylist(const QString &name, const QStringList &newListOfSongs, QMediaPlaylist *currentPlaylist)
{
    if(name == "" && newListOfSongs.isEmpty())
        return false;

    cd->setCurrent(QCoreApplication::applicationDirPath());
    currentPlaylist->clear();

    //add song into playlist
    for(const QString &iter : newListOfSongs)
        currentPlaylist->addMedia(QMediaContent(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/music/" + iter)));

    if(currentPlaylist->save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + name + ".m3u8"), "m3u8"))
        return true;
    else
        return false;
}

bool Playlist::SavePlaylist(const QString &name, const QStringList &newListOfSongs)
{
    if(name == "" && newListOfSongs.isEmpty())
        return false;

    cd->setCurrent(QCoreApplication::applicationDirPath());

    QMediaPlaylist *bufferPlaylist = new QMediaPlaylist();

    //add song into playlist
    for(const QString &iter : newListOfSongs)
        bufferPlaylist->addMedia(QMediaContent(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/music/" + iter)));

    if(bufferPlaylist->save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + name + ".m3u8"), "m3u8"))
    {
        delete bufferPlaylist;
        return true;
    }
    else
    {
        delete bufferPlaylist;
        return false;
    }
}

bool Playlist::SavePlaylist(const QString &name)
{
    if(name == "")
        return false;

    QMediaPlaylist *bufferPlaylist = new QMediaPlaylist();

    if(bufferPlaylist->save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + name + ".m3u8"), "m3u8"))
    {
        delete bufferPlaylist;
        return true;
    }
    else
    {
        delete bufferPlaylist;
        return false;
    }
}
/*---------------------------------------SAVE METHODS---------------------------------------*/


/*--------------------------------------RENAME METHODS--------------------------------------*/
bool Playlist::RenamePlayList(const QString &newName, QMediaPlaylist *currentPlaylist)
{
    if(newName == "")
        return false;

    cd->setCurrent(QCoreApplication::applicationDirPath());

    if(currentPlaylist->save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + newName + ".m3u8"), "m3u8"))
        return true;
    else
        return false;
}

bool Playlist::RenamePlayList(const QString &newName, const QString &currentName)
{
    if((newName == "") || (currentName == ""))
        return false;

    cd->setCurrent(QCoreApplication::applicationDirPath());

    QFile *bufferPlaylist = new QFile();
    bufferPlaylist->setFileName(QCoreApplication::applicationDirPath() + "/bin/" + currentName + ".m3u8");

    if(bufferPlaylist->rename(QCoreApplication::applicationDirPath() + "/bin/" + newName + ".m3u8"))
    {
        delete bufferPlaylist;
        return true;
    }
    else
    {
        delete bufferPlaylist;
        return false;
    }
}
/*--------------------------------------RENAME METHODS--------------------------------------*/


/*----------------------------------------SETTINGS METHODS------------------------------------*/
bool Playlist::CheckSettingsDir()
{
    if(QDir("bin").QDir::exists() == false)
    {
        cd->mkdir("bin");
        return false;
    }
    else
        return true;
}
/*----------------------------------------SETTINGS METHODS------------------------------------*/


/*------------------------------------------ADD METHODS--------------------------------------*/
bool Playlist::AddSongIntoPlayListByName(const QString &song, const QString &nameOfPlayList, const QString &nameOfCurrentPlayList, const int &index)
{
    if((song == "") && (nameOfPlayList == ""))
        return false;

    cd->setCurrent(QCoreApplication::applicationDirPath()); // set default path
    const QString formatOfSong = ParserToGetFormatOfSong(nameOfCurrentPlayList, index); // get format by index inside selected playlist

    QMediaPlaylist *bufferPlaylist = new QMediaPlaylist();
    bufferPlaylist->load(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + nameOfPlayList + ".m3u8"), "m3u8"); // load playlist
    bufferPlaylist->addMedia(QMediaContent(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/music/" + song + formatOfSong)));

    if(bufferPlaylist->save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + nameOfPlayList + ".m3u8"), "m3u8"))
    {
        delete bufferPlaylist;
        return true;
    }
    else
    {
        delete bufferPlaylist;
        return false;
    }
}

bool Playlist::AddSongsIntoPlayListByName(const QStringList &songs, const QString &nameOfPlayList)
{
    if((songs.isEmpty()) && (nameOfPlayList == ""))
        return false;

    //set default path
    cd->setCurrent(QCoreApplication::applicationDirPath());

    QMediaPlaylist *bufferPlaylist = new QMediaPlaylist();
    bufferPlaylist->load(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + nameOfPlayList + ".m3u8"), "m3u8"); // load playlist

    //add songs into playlist
    foreach(const QString &iter, songs)
        bufferPlaylist->addMedia(QMediaContent(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/music/" + iter)));

    if(bufferPlaylist->save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + nameOfPlayList + ".m3u8"), "m3u8"))
    {
        delete bufferPlaylist;
        return true;
    }
    else
    {
        delete bufferPlaylist;
        return false;
    }
}

bool Playlist::AddSongsIntoCurrentPlayList(const QStringList &songs)
{
    if(songs.isEmpty())
        return false;

    cd->setCurrent(QCoreApplication::applicationDirPath()); // set default path

    //add songs into current playlist
    foreach(const QString &iter, songs)
        currentPlaylist->addMedia(QMediaContent(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/music/" + iter)));

    if(currentPlaylist->save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + currentPlaylistName + ".m3u8"), "m3u8"))
        return true;
    else
        return false;
}
/*------------------------------------------ADD METHODS--------------------------------------*/


/*--------------------------------------REMOVE METHODS--------------------------------------*/
bool Playlist::RemoveTrackByIndex(const int &index)
{
    QFile *buffer = new QFile(QCoreApplication::applicationDirPath() + "/bin/" + currentPlaylistName + ".m3u8");
    QTextStream stream(buffer);
    QString fullpathOfTrack = "";

    if(buffer->open(QIODevice::ReadOnly))
    {
        // read specific line by index
        for(int iterOfFile = 0; iterOfFile < index; ++iterOfFile)
            fullpathOfTrack = stream.readLine().trimmed();

        delete buffer;
    }
    else
    {
        delete buffer;
        return false;
    }

    if(currentPlaylist->removeMedia(index))
    {
        if(currentPlaylist->save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + currentPlaylistName + ".m3u8"), "m3u8"))
            return true;
        else
            return false;
    }
    else
        return false;
}

bool Playlist::RemoveTrackByIndexFromApp(const int &index)
{
    QFile *buffer = new QFile(QCoreApplication::applicationDirPath() + "/bin/all.m3u8");
    QMediaPlaylist *bufferAll = new QMediaPlaylist();
    bufferAll->load(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/all.m3u8"), "m3u8");

    QTextStream stream(buffer);
    QString fullpathOfTrack = "";

    if(buffer->open(QIODevice::ReadOnly))
    {
        // read specific line by index
        for(int iterOfFile = 0; iterOfFile <= index; ++iterOfFile)
            fullpathOfTrack = stream.readLine().trimmed();

        delete buffer;
    }
    else
    {
        delete buffer;
        return false;
    }

    if(bufferAll->removeMedia(index))
    {
        //path of file with unicode
        fullpathOfTrack.remove(0, 8);
        //added '/' for UNIX (macOS/Linux)
        fullpathOfTrack.push_front("/");

        //check Windows paths
        QString::const_iterator iterator = fullpathOfTrack.begin() + 2;
        if(*iterator == ":")
            fullpathOfTrack.remove(0, 1);

        //remove track from app by index
        QFile removeTrack(fullpathOfTrack);
        removeTrack.remove();

        if(bufferAll->save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/all.m3u8"), "m3u8"))
            return true;
        else
            return false;
    }
    else
        return false;
}

bool Playlist::RemoveTrackByIndex(const int &index, const QString &name)
{
   QMediaPlaylist *buffer = new QMediaPlaylist();
   buffer->load(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + name + ".m3u8"), "m3u8");

   if(buffer->removeMedia(index))
   {
       if(buffer->save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + name + ".m3u8"), "m3u8"))
       {
           delete buffer;
           return true;
       }
       else
       {
           delete buffer;
           return false;
       }
   }
   else
   {
       delete buffer;
       return false;
   }
}

bool Playlist::RemoveAllTracks()
{
    if(currentPlaylist->clear())
    {
        if(currentPlaylist->save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + currentPlaylistName + ".m3u8"), "m3u8"))
            return true;
        else
            return false;
    }
    else
        return false;
}

bool Playlist::RemoveAllTracksFromApp()
{
    QMediaPlaylist *buffer = new QMediaPlaylist();
    buffer->load(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/all.m3u8"), "m3u8");

    buffer->clear();

    //delete all tracks from app
    for(const QString &iter : allSongs)
        cd->remove(QCoreApplication::applicationDirPath() + "/music/" + iter);

    if(buffer->save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/all.m3u8"), "m3u8"))
    {
        delete buffer;
        return true;
    }
    else
    {
        delete buffer;
        return false;
    }
}

bool Playlist::RemoveAllTracks(const QString &name)
{
    QMediaPlaylist *buffer = new QMediaPlaylist();
    buffer->load(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + name + ".m3u8"), "m3u8");

    buffer->clear();

    if(buffer->save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + name + ".m3u8"), "m3u8"))
    {
        delete buffer;
        return true;
    }
    else
    {
        delete buffer;
        return false;
    }
}
/*--------------------------------------REMOVE METHODS--------------------------------------*/


/*---------------------------------------MOVE METHODS---------------------------------------*/
bool Playlist::MoveSongInsidePlaylistByIndex(const int &currentIndex, const int &newIndex)
{
    currentPlaylist->moveMedia(currentIndex, newIndex);

    if(currentPlaylist->save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + currentPlaylistName + ".m3u8"), "m3u8"))
        return true;
    else
        return false;
}

bool Playlist::MoveSongInsidePlaylistByIndex(const int &currentIndex, const int &newIndex, const QString &name)
{
    QMediaPlaylist *buffer = new QMediaPlaylist();
    buffer->load(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + name + ".m3u8"), "m3u8");

    buffer->moveMedia(currentIndex, newIndex);

    if(buffer->save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + name + ".m3u8"), "m3u8"))
    {
        delete buffer;
        return true;
    }
    else
    {
        delete buffer;
        return false;
    }
}
/*---------------------------------------MOVE METHODS---------------------------------------*/

/*--------------------------------------RENAME NAME OF TRACK--------------------------------*/
bool Playlist::RenameTrack(const int &index, const QString &playlist, const QString &newName)
{
    if(newName == "")
        return false;

    //-----------------------------------------------------------------------------------------------Rename in current playlist

    QFile *fileOfCurrentPlaylist = new QFile(QCoreApplication::applicationDirPath() + "/bin/" + playlist + ".m3u8");
    QTextStream streamOfCurrentPlaylist(fileOfCurrentPlaylist);
    QString bufferOfName = "";
    QString newNameOfTrack = "";

    bool OS = false; //false == Windows || true == Unix

    if(fileOfCurrentPlaylist->open(QIODevice::ReadWrite))
    {
        //read specific line by index
        for(int iterOfFile = 0; iterOfFile <= index; ++iterOfFile)
            bufferOfName = streamOfCurrentPlaylist.readLine(0);

        QFile *fileOfTrack = new QFile();

        //-----------------------------------------------------------------------------------------------Read data of path and rename it

        //path of file with unicode
        bufferOfName.remove(0, 8);
        //added '/' for UNIX (macOS/Linux)
        bufferOfName.push_front("/");

        //check Windows paths
        QString::const_iterator iterator = bufferOfName.begin() + 2;
        if(*iterator == ":")
            bufferOfName.remove(0, 1);
        else
            OS = true;// Set Unix OS (macOS/Linux)

        //get only name with format from full path
        bufferOfName = ParseToGetCurrentName(bufferOfName);

        //file with current name
        fileOfTrack->setFileName(QCoreApplication::applicationDirPath() + "/music/" + bufferOfName);

        //Create new name of track
        newNameOfTrack = QCoreApplication::applicationDirPath() + "/music/" + newName + ParseStringToGetFormat(bufferOfName);

        //rename file
        fileOfTrack->rename(QCoreApplication::applicationDirPath() + "/music/" + bufferOfName, //current path
                            newNameOfTrack); //new path (like new name)

        //check Windows paths to add it to current OS
        QString::const_iterator iterOfPath = newNameOfTrack.begin() + 1;
        if(*iterOfPath == ":")//Windows
            newNameOfTrack.push_front("file:///");
        else//UNIX (macOS/Linux)
            newNameOfTrack.push_front("file://");

        delete fileOfTrack;

        //-----------------------------------------------------------------------------------------------Read data of path and rename it
    }

    //-----------------------------------------------------------------------------------------------Rename in current playlist


    //-----------------------------------------------------------------------------------------------Rename in other playlist

    const QStringList listOfAllPlayLists = this->GetAllPlaylists();

    //iter all playlist to rename in all playlist
    for(const QString &currentPlaylist : listOfAllPlayLists)
    {
        QFile fileOfPlaylist(QCoreApplication::applicationDirPath() + "/bin/" + currentPlaylist);

        if(fileOfPlaylist.open(QIODevice::ReadWrite))
        {
            QTextStream stream(&fileOfPlaylist);

            //-----------------------------------------------------------------------------------------------Write data into file after rename

            //refactore playlist file
            QStringList streamData;
            QString line = "";
            QString pathBuffer = "";

            if(!OS)
                //Windows
                pathBuffer = "file:///" + QCoreApplication::applicationDirPath() + "/music/" + bufferOfName;
            else
                //Unix
                pathBuffer = "file://" + QCoreApplication::applicationDirPath() + "/music/" + bufferOfName;

            //reset stream to start read from beginning
            stream.seek(0);

            //Parsing file to add into buffer all songs except old name
            while(!stream.atEnd())
            {
                //Read line
                line = stream.readLine(0).trimmed();

                //CMP current line and old name
                if(!(line == pathBuffer))
                    streamData.push_back(line + "\n");
            }

            //write new name into file
            streamData.push_back(newNameOfTrack + "\n");

            //clear playlist
            fileOfPlaylist.resize(0);
            //write buffer
            for(const QString &iter : streamData)
                stream << iter;
            //-----------------------------------------------------------------------------------------------Write data into file after rename

            fileOfPlaylist.close();
        }
    }

    //-----------------------------------------------------------------------------------------------Rename in other playlist

    return true;
}
/*--------------------------------------RENAME NAME OF TRACK--------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||METHODS PRIVATE||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||PARSERS||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
QString Playlist::ParserToGetNameOfSongByIndex(const int &index)
{
    QFile buffer(QCoreApplication::applicationDirPath() + "/bin/" + currentPlaylistName + ".m3u8");
    QString name = "";

    if(buffer.open(QIODevice::ReadOnly))
    {
        QTextStream playRead(&buffer);

        // read specific line by index
        for(int iterOfFile = 0; iterOfFile <= index; ++iterOfFile)
            name = playRead.readLine().trimmed();

        //get only name from current path
        name = ParseStringToRemoveFormatAndCurrentPath(name);

        buffer.close();
    }

    return name;
}

QStringList Playlist::ParseToGetFullPathOfTracks(const QStringList &list)
{
    cd->setCurrent(QCoreApplication::applicationDirPath() + "/music/");
    QStringList allSongs = cd->entryList(QStringList() << "*.mp3" << "*.MP3" << "*.wav" << "*.WAV" << "*.m4a" << "*.M4A", QDir::Files);
    cd->setCurrent(QCoreApplication::applicationDirPath());

    QStringList bufferlist = {}; //july.mp3 //july

    //Parsing all files from app
    for(const QString &iterForAllSongs : allSongs)
    {
        //start after dot
        QString::const_iterator iter = iterForAllSongs.end() - 5;
        QString buffer = "";

        for(; iter != iterForAllSongs.begin() - 1; --iter)
        {
                //unix like      //windows
            if(!(*iter == "/") || !(*iter == "\\"))
                buffer.push_front(*iter); //if char not '/' or '\' write chat into buffer
            else
                break; //else just break cycle
        }
        //now buffer = 'july'

        //Add track without full path and format into buffer
        for(const QString &iterForList : list)
            if(iterForList == buffer)
                bufferlist.push_back(QCoreApplication::applicationDirPath() + "/music/" + iterForAllSongs);
    }

    return bufferlist;
}

QString Playlist::ParseStringToRemoveFormatAndCurrentPath(const QString &string)
{
    //Remove last char UNICODE
    QString::const_iterator iter = string.end() - 1;
    QString buffer = "";

    //Check last char again
    if(*iter == "8")
        iter = string.end() - 6;
    else
        iter = string.end() - 5;

    //Parsing string while not char '/' or '\'
    for(; iter != string.begin() - 1; --iter)
            //unix like      //windows
        if(*iter == "/" || *iter == "\\")
            //Stop  parsing
            break;
        else
            //Push char into buffer
            buffer.push_front(*iter);

    return buffer;
}

QString Playlist::ParserToGetFormatOfSong(const QString &nameOfPlayList, const int &index)
{
    if(nameOfPlayList == "")
        return "";

    //load file
    QFile buffer(QCoreApplication::applicationDirPath() + "/bin/" + nameOfPlayList + ".m3u8");
    QString format = "";

    if(buffer.open(QIODevice::ReadOnly))
    {
        QTextStream playRead(&buffer);

        // read specific line by index
        for(int iterOfFile = 0; iterOfFile <= index; ++iterOfFile)
            format = playRead.readLine().trimmed();

        // parse string to get format of song
        format != "" ? format = ParseStringToGetFormat(format) : format = "";
    }

    return format;
}

QString Playlist::ParseStringToGetFormat(const QString &string)
{
    //Remove last char UNICODE
    QString::const_iterator iter = string.end() - 1;
    QString buffer = "";

    //Parsing string to get last 3 chars (format)
    for(; iter != string.begin(); --iter)
    {
        //Check if current index is dot
        if(*iter == ".")
        {
            //Push dot after get all chars of format
            buffer.push_front(".");
            //and return format with dot like '.wav'
            return buffer;
        }
        else//Save one char from format of file
            buffer.push_front(*iter);
    }

    //Save return
    return buffer;
}

QString Playlist::ParseToGetCurrentName(const QString &fullPath)
{
    QString nameWithFormat = "";
    QString bufferOfFullPath = fullPath;
    QString::iterator iterator = bufferOfFullPath.end();

    //Check UNICODE char int the end
    if(*iterator == NULL)
        iterator = bufferOfFullPath.end() - 1;

    //Parsing string (full path) to get only name of track with format
    for(; iterator != bufferOfFullPath.begin(); --iterator)
    {
            //unix like         //windows
        if((*iterator == "/") || (*iterator == "\\"))
            return nameWithFormat;
        else//Save char of only name
            nameWithFormat.push_front(*iterator);
    }

    return nameWithFormat;
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||PARSERS||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
