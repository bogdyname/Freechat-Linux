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
Playlist::Playlist()
{
    try
    {
        Playlist::cd = new QDir();
        Playlist::currentPlaylist = new QMediaPlaylist();
    }
    catch(std::bad_alloc &exp)
    {
        #ifndef Q_DEBUG
        qCritical() << "Exception caught: " << exp.std::bad_alloc::what();
        #endif
        abort();
    }
    catch(...)
    {
        #ifndef Q_DEBUG
        qCritical() << "Some exception caught";
        #endif
        abort();
    }

    //Check default playlist
    if(!QFile::exists(QCoreApplication::applicationDirPath() + "/bin/all.m3u"))
    {
        //Create playlist with all songs
        //For get all songs into 'allSongs' variable
        Playlist::cd->QDir::setCurrent(QCoreApplication::applicationDirPath() + "/music/");
        Playlist::allSongs = Playlist::cd->QDir::entryList(QStringList() << "*.mp3" << "*.MP3" << "*.wav" << "*.WAV", QDir::Files);

        QMediaPlaylist *buffer = new QMediaPlaylist();

        for(const QString &iter : Playlist::allSongs)
            buffer->QMediaPlaylist::addMedia(QMediaContent(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/music/" + iter)));//add song into playlist

        if(buffer->QMediaPlaylist::save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/all.m3u"), "m3u"))
            delete buffer;

        qDebug() << "Playlist 'all' created";
    }
    else
    {
        //Reboot songs inside playlist with all songs
        //For get all songs into 'allSongs' variable
        Playlist::cd->QDir::setCurrent(QCoreApplication::applicationDirPath() + "/music/");
        Playlist::allSongs = Playlist::cd->QDir::entryList(QStringList() << "*.mp3" << "*.MP3" << "*.wav" << "*.WAV", QDir::Files);

        QMediaPlaylist *buffer = new QMediaPlaylist();

        buffer->QMediaPlaylist::load(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/all.m3u"), "m3u");
        buffer->QMediaPlaylist::clear();

        for(const QString &iter : Playlist::allSongs)
            buffer->QMediaPlaylist::addMedia(QMediaContent(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/music/" + iter)));//add song into playlist

        if(buffer->QMediaPlaylist::save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/all.m3u"), "m3u"))
            delete buffer;

        qDebug() << "Playlist 'all' already exists!";
    }

    //For bin folder
    Playlist::cd->QDir::setCurrent(QCoreApplication::applicationDirPath());

    //Check folder of settings/playlist
    if(Playlist::cd->QDir::mkdir("bin"))
        qDebug() << "Folder 'bin' created";
    else
        qDebug() << "Folder 'bin' already exists!";

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
     * Add ----------------------------
        6.1) add song into playlist by index
        6.2) add song into platlist from all songs (default playlist)
        6.3) add tracks into NEW playlist
    */
    //Save
    QObject::connect(this, &Playlist::CallOutSaveCurrentPlayList, this, &Playlist::SaveCurrentPlayList);
    QObject::connect(this, &Playlist::CallOutSaveSelectedPlayList, this, &Playlist::SaveSelectedPlayList);
    QObject::connect(this, &Playlist::CallOutSaveNewPlayList, this, &Playlist::SaveNewPlayList);
    //Rename
    QObject::connect(this, &Playlist::CallOutRenameCurrentPlayList, this, &Playlist::RenameCurrentPlayList);
    QObject::connect(this, &Playlist::CallOutRenameSelectedPlayList, this, &Playlist::RenameSelectedPlayList);
    //Name
    QObject::connect(this, &Playlist::CallOutSetCurrentPlayListName, this, &Playlist::SetCurrentPlayListName);
    //Create
    QObject::connect(this, &Playlist::CallOutCreateNewPlayList, this, &Playlist::CreateNewPlayList);
    //Remove
    QObject::connect(this, &Playlist::CallOutRemovePlayListByName, this, &Playlist::RemovePlayListByName);
    //Add song
    QObject::connect(this, &Playlist::CallOutAddSongIntoPlayList, this, &Playlist::AddSongIntoPlayList);
    QObject::connect(this, &Playlist::CallOutAddSongIntoPlayListFromDefaultPlayList, this, &Playlist::AddSongIntoPlayListFromDefaultPlayList);

    return;
}

Playlist::~Playlist()
{
    delete Playlist::cd;
    delete Playlist::currentPlaylist;

    return;
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||MAIN|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||SLOTS PRIVATE||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
void Playlist::SaveCurrentPlayList(const QString &name, const QStringList &newListOfSongs, QMediaPlaylist *currentPlaylist)
{
    if(name == "" && newListOfSongs.QStringList::isEmpty())
        return;

    if(Playlist::SavePlaylist(name, newListOfSongs, currentPlaylist))
        #ifndef Q_DEBUG
        qDebug() << "playlist successed saved";
        #endif
    else
        #ifndef Q_DEBUG
        qCritical() << "error: can't save playlist";
        #endif

    return;
}

void Playlist::SaveSelectedPlayList(const QString &name, const QStringList &newListOfSongs)
{
    if(name == "" && newListOfSongs.QStringList::isEmpty())
        return;

    if(Playlist::SavePlaylist(name, newListOfSongs))
        #ifndef Q_DEBUG
        qDebug() << "playlist successed saved";
        #endif
    else
        #ifndef Q_DEBUG
        qCritical() << "error: can't save playlist";
        #endif

    return;
}

void Playlist::SaveNewPlayList(const QString &name)
{
    if(name == "")
        return;

    if(Playlist::SavePlaylist(name))
        #ifndef Q_DEBUG
        qDebug() << "playlist successed saved";
        #endif
    else
        #ifndef Q_DEBUG
        qCritical() << "error: can't save playlist";
        #endif

    return;
}

void Playlist::RenameCurrentPlayList(const QString &newName, QMediaPlaylist *currentPlaylist)
{
    if(newName == "")
        return;

    if(Playlist::RenamePlayList(newName, currentPlaylist))
        #ifndef Q_DEBUG
        qDebug() << "playlist successed renamed with new name: " << newName;
        #endif
    else
        #ifndef Q_DEBUG
        qCritical() << "error: can't rename playlist " << newName;
        #endif
}

void Playlist::RenameSelectedPlayList(const QString &newName, const QString &currentName)
{
    if((newName == "") && (currentName == ""))
        return;

    if(Playlist::RenamePlayList(newName, currentName))
    {
        #ifndef Q_DEBUG
        qDebug() << "Playlist name: " << currentName;
        qDebug() << "Playlist new name: " << newName;
        qDebug() << "playlist successed renamed";
        #endif
    }
    else
        #ifndef Q_DEBUG
        qCritical() << "error: can't rename playlist";
        #endif

    return;
}

void Playlist::SetCurrentPlayListName(const QString &nameOfCurrentPlaylist)
{
    Playlist::currentPlaylistName.QString::clear();
    Playlist::currentPlaylistName += nameOfCurrentPlaylist;

    return;
}

void Playlist::CreateNewPlayList(const QString &name, const QStringList &tracks)
{
    if(name == "")
        return;

    if(Playlist::CreatePlayList(name, tracks))
        #ifndef Q_DEBUG
        qDebug() << "play list successed created! " + name;
        #endif
    else
        #ifndef Q_DEBUG
        qCritical() << "error create play list! " + name;
        #endif

    return;
}

void Playlist::RemovePlayListByName(const QString &name)
{
    if(name == "")
        return;

    if(Playlist::RemovePlayList(name))
        #ifndef Q_DEBUG
        qDebug() << "playlist successed removed: " << name;
        #endif
    else
        #ifndef Q_DEBUG
        qCritical() << "error: can't remove playlist " << name;
        #endif

    return;
}

void Playlist::AddSongIntoPlayList(const QString &song, const QString &nameOfPlayList, const QString &nameOfCurrentPlayList, const unsigned short int &index)
{
    if(Playlist::AddSongIntoPlayListByName(song, nameOfPlayList, nameOfCurrentPlayList, index))
        #ifndef Q_DEBUG
        qDebug() << "song successed added into '" << nameOfPlayList << "' -" << song;
        #endif
    else
        #ifndef Q_DEBUG
        qCritical() << "error: can't add sog into playlist '" << nameOfPlayList << "' -" << song;
        #endif

    return;
}

void Playlist::AddSongIntoPlayListFromDefaultPlayList(const QString &song, const QString &nameOfPlayList, const unsigned short int &index)
{
    if(Playlist::AddSongIntoPlayListByName(song, nameOfPlayList, "default", index))
        #ifndef Q_DEBUG
        qDebug() << "song successed added into '" << nameOfPlayList << "' -" << song;
        #endif
    else
        #ifndef Q_DEBUG
        qCritical() << "error: can't add sog into playlist '" << nameOfPlayList << "' -" << song;
        #endif

    return;
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||SLOTS PRIVATE||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||SLOTS PUBLIC|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
void Playlist::SetNextTrack()
{
    Playlist::currentPlaylist->QMediaPlaylist::next();

    return;
}

void Playlist::SetPreviousTrack()
{
    Playlist::currentPlaylist->QMediaPlaylist::previous();

    return;
}

void Playlist::SetTrackByIndex(QListWidgetItem *indexOfTrack)
{
    const unsigned short int index = indexOfTrack->listWidget()->row(indexOfTrack);
    Playlist::currentPlaylist->QMediaPlaylist::setCurrentIndex(index);

    return;
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||SLOTS PUBLIC|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||METHODS PUBLIC|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
QString Playlist::GetCurrentPlayListName()
{
    return Playlist::currentPlaylistName;
}

QMediaPlaylist* Playlist::GetCurrentPlayList()
{
    return Playlist::currentPlaylist;
}

void Playlist::LoadPlayList(const QString &name)
{
    if(Playlist::LookingForPlayList(name, Playlist::currentPlaylist))
        qDebug() << "loaded playlist";
    else
        qCritical() << "error: can't load playlist";

    return;
}

QStringList Playlist::GetSongsFromCurrentPlayList(const QString &nameOfPlayList)
{
    QStringList songs = {};

    if((nameOfPlayList == "") && (Playlist::CheckSettingsDir() == false))
        return songs;

    //path to file
    const QString path = QCoreApplication::applicationDirPath() + "/bin/" + nameOfPlayList;

    QFile file;
    file.QFile::setFileName(path);

    qDebug() << path;

    if(file.QFile::exists())
    {
        if(!file.QFile::open(QFile::ReadOnly))
            qCritical() << "error: can't open playlist";
        else
        {
            QTextStream stream(&file);

            while(!stream.QTextStream::atEnd())
                songs.QList::push_back(stream.QTextStream::readLine());

            file.QFile::close();
        }
    }
    else
        qCritical() << "error: file not exists";

    return songs;
}

const QStringList Playlist::GetAllTracks()
{
    return Playlist::allSongs;
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||METHODS PUBLIC|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||METHODS PRIVATE||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
bool Playlist::CreatePlayList(const QString &name, const QStringList &list)
{
    if((name == "") || (list.QStringList::isEmpty()))
        return false;

    Playlist::CheckSettingsDir();
    Playlist::cd->QDir::setCurrent(QCoreApplication::applicationDirPath());

    QMediaPlaylist *bufferPlaylist = new QMediaPlaylist();

    for(const QString &iter : list)
        bufferPlaylist->QMediaPlaylist::addMedia(QMediaContent(QUrl::fromLocalFile(iter)));//add song into playlist

    if(bufferPlaylist->QMediaPlaylist::save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + name + ".m3u"), "m3u"))
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

bool Playlist::RemovePlayList(const QString &name)
{
    if(name == "")
        return false;

    Playlist::CheckSettingsDir();

    QFile buffer(QCoreApplication::applicationDirPath() + "/bin/" + name + ".m3u");

    if(buffer.QFile::remove())
        return true;
    else
        return false;
}

bool Playlist::LookingForPlayList(const QString &name, QMediaPlaylist *medialist)
{
    if(name == "")
        return false;

    Playlist::CheckSettingsDir();

    medialist->QMediaPlaylist::clear();
    medialist->QMediaPlaylist::load(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + name), "m3u");
    medialist->setCurrentIndex(1);

    if(!medialist->QMediaPlaylist::isEmpty())
        return true;
    else
        return false;
}

bool Playlist::SavePlaylist(const QString &name, const QStringList &newListOfSongs, QMediaPlaylist *currentPlaylist)
{
    if(name == "" && newListOfSongs.QStringList::isEmpty())
        return false;

    Playlist::cd->QDir::setCurrent(QCoreApplication::applicationDirPath());
    currentPlaylist->QMediaPlaylist::clear();

    for(const QString &iter : newListOfSongs)
    {
        currentPlaylist->QMediaPlaylist::addMedia(QMediaContent(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/music/" + iter)));

        #ifndef Q_DEBUG
        qDebug() << iter;
        qDebug() << currentPlaylist->QMediaPlaylist::mediaCount();
        #endif
    }

    if(currentPlaylist->QMediaPlaylist::save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + name + ".m3u"), "m3u"))
        return true;
    else
        return false;
}

bool Playlist::SavePlaylist(const QString &name, const QStringList &newListOfSongs)
{
    if(name == "" && newListOfSongs.QStringList::isEmpty())
        return false;

    Playlist::cd->QDir::setCurrent(QCoreApplication::applicationDirPath());

    QMediaPlaylist *bufferPlaylist = new QMediaPlaylist();

    for(const QString &iter : newListOfSongs)
    {
        bufferPlaylist->QMediaPlaylist::addMedia(QMediaContent(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/music/" + iter)));

        #ifndef Q_DEBUG
        qDebug() << iter;
        qDebug() << bufferPlaylist->QMediaPlaylist::mediaCount();
        #endif
    }

    if(bufferPlaylist->QMediaPlaylist::save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + name + ".m3u"), "m3u"))
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

    if(bufferPlaylist->QMediaPlaylist::save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + name + ".m3u"), "m3u"))
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

bool Playlist::RenamePlayList(const QString &newName, QMediaPlaylist *currentPlaylist)
{
    if(newName == "")
        return false;

    Playlist::cd->QDir::setCurrent(QCoreApplication::applicationDirPath());

    if(currentPlaylist->QMediaPlaylist::save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + newName + ".m3u"), "m3u"))
        return true;
    else
        return false;
}

bool Playlist::RenamePlayList(const QString &newName, const QString &currentName)
{
    if((newName == "") && (currentName == ""))
        return false;

    Playlist::cd->QDir::setCurrent(QCoreApplication::applicationDirPath());

    QMediaPlaylist *bufferPlaylist = new QMediaPlaylist();
    bufferPlaylist->QMediaPlaylist::load(QCoreApplication::applicationDirPath() + "/bin/" + currentName + "m3u");

    if(bufferPlaylist->QMediaPlaylist::save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + newName + ".m3u"), "m3u"))
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

bool Playlist::CheckSettingsDir()
{
    if(QDir("bin").QDir::exists() == false)
    {
        Playlist::cd->QDir::mkdir("bin");

        qDebug() << "Folder 'bin' created";

        return false;
    }
    else
    {
        qCritical() << "Folder 'bin' already exists!";

        return true;
    }
}

bool Playlist::AddSongIntoPlayListByName(const QString &song, const QString &nameOfPlayList, const QString &nameOfCurrentPlayList, const unsigned short int &index)
{
    if((song == "") && (nameOfPlayList == ""))
        return false;

    Playlist::cd->QDir::setCurrent(QCoreApplication::applicationDirPath()); // set default playlist
    const QString formatOfSong = Playlist::GetFormatOfSong(nameOfCurrentPlayList, index); // get format by index inside current playlist

    QMediaPlaylist *bufferPlaylist = new QMediaPlaylist();
    bufferPlaylist->QMediaPlaylist::load(QCoreApplication::applicationDirPath() + "/bin/" + nameOfPlayList, "m3u"); // load playlist
    bufferPlaylist->QMediaPlaylist::addMedia(QMediaContent(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/music/" + song + formatOfSong)));

    if(bufferPlaylist->QMediaPlaylist::save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + nameOfPlayList + ".m3u"), "m3u"))
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

QString Playlist::GetFormatOfSong(const QString &nameOfPlayList, const unsigned short int &index)
{
    if(nameOfPlayList == "")
        return "";

    QFile buffer(QCoreApplication::applicationDirPath() + "/bin/" + nameOfPlayList + ".m3u");
    QString format = "";

    if(buffer.QIODevice::open(QIODevice::ReadOnly))
    {
        QTextStream playRead(&buffer);

        // read specific line by index
        for(unsigned short int iterOfFile = 0; iterOfFile < index; ++iterOfFile)
            format = playRead.QTextStream::readLine().QString::trimmed();

        // parse string to get format of song
        format != "" ? format = Playlist::ParseStringToGetFormat(format) : format = "";
    }

    return format;
}

QString Playlist::ParseStringToGetFormat(const QString &string)
{
    QString::const_iterator iter = string.QString::end();
    QString buffer = "";

    for(; iter != string.QString::begin(); --iter)
    {
        if(*iter == ".")
        {
            buffer.QString::push_front(".");
            return buffer;
        }
        else
        {
            buffer.QString::push_front(*iter);
        }
    }

    return buffer;
}

QStringList Playlist::ParseToGetFullPathOfTracks(const QStringList &list)
{
    Playlist::cd->QDir::setCurrent(QCoreApplication::applicationDirPath() + "/music/");
    QStringList allSongs = Playlist::cd->QDir::entryList(QStringList() << "*.mp3" << "*.MP3" << "*.wav" << "*.WAV", QDir::Files);
    Playlist::cd->QDir::setCurrent(QCoreApplication::applicationDirPath());

    QStringList bufferlist = {}; //july.mp3 //july

    for(const QString &iterForAllSongs : allSongs)
    {
        QString::const_iterator iter = iterForAllSongs.QString::end() - 5; //start after dot
        QString buffer = "";

        qDebug() << "buffer: " << buffer;
        qDebug() << "list: " << iterForAllSongs;

        for(; iter != iterForAllSongs.QString::begin() - 1; --iter)
        {
                //unix like      //windows
            if(!(*iter == "/") || !(*iter == "\\"))
                buffer.QString::push_front(*iter); //if char not '/' or '\' write chat into buffer
            else
                break; //else just break cycle
        }
        //now buffer = 'july'

        for(const QString &iterForList : list)
            if(iterForList == buffer)
            {
                qDebug() << "buffer: " << buffer;
                qDebug() << "list: " << iterForList;
                bufferlist.QStringList::push_back(QCoreApplication::applicationDirPath() + "/music/" + iterForAllSongs);
            }
    }

    return bufferlist;
}

QString Playlist::ParseStringToRemoveFormatAndCurrentPath(const QString &string)
{
    QString::const_iterator iter = string.QString::end() - 5;
    QString buffer = "";

    qDebug() << "FULL PATH: " << string;

    for(; iter != string.QString::begin() - 1; --iter)
        if(*iter == "/" || *iter == "\\")
            break;
        else
            buffer.QString::push_front(*iter);

    return buffer;
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||METHODS PRIVATE||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
