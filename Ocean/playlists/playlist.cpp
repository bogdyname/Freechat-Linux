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
        Playlist::settingsDir = new QDir();
        Playlist::dialog = new QFileDialog();
        Playlist::currentPlaylist = new QMediaPlaylist();
        Playlist::defaultPlaylist = new QMediaPlaylist();
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

    //current path of app
    Playlist::dialog->QFileDialog::setDirectory(QCoreApplication::applicationDirPath());

    //For get all songs into 'allSongs' variable
    Playlist::settingsDir->QDir::setCurrent(QCoreApplication::applicationDirPath() + "/music/");
    Playlist::allSongs = Playlist::settingsDir->QDir::entryList(QDir::AllEntries);

    //For bin folder
    Playlist::settingsDir->QDir::setCurrent(QCoreApplication::applicationDirPath());

    //Check folder of settings/playlist
    if(Playlist::settingsDir->QDir::mkdir("bin"))
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
    delete Playlist::settingsDir;
    delete Playlist::dialog;
    delete Playlist::currentPlaylist;
    delete Playlist::defaultPlaylist;

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

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Playlist::SetCurrentPlayListName(const QString &nameOfCurrentPlaylist)
{
    Playlist::currentPlaylistName.QString::clear();
    Playlist::currentPlaylistName += nameOfCurrentPlaylist;

    return;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Playlist::CreateNewPlayList(const QString &name)
{
    if(name == "")
        return;

    const QStringList songs = Playlist::dialog->QFileDialog::getOpenFileNames(0, "Create play list", "", "*.mp3 *.wav");

    if(songs.QList::isEmpty())
        return;
    else
        if(Playlist::CreatePlayList(name, songs))
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
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Playlist::SetNextTrack()
{
    if(Playlist::currentPlaylistName == "all")
        Playlist::defaultPlaylist->QMediaPlaylist::next();
    else
        Playlist::currentPlaylist->QMediaPlaylist::next();

    return;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Playlist::SetPreviousTrack()
{
    if(Playlist::currentPlaylistName == "all")
        Playlist::defaultPlaylist->QMediaPlaylist::previous();
    else
        Playlist::currentPlaylist->QMediaPlaylist::previous();

    return;
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||SLOTS PUBLIC|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||METHODS PUBLIC|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
QString Playlist::GetCurrentPlayListName()
{
    return Playlist::currentPlaylistName;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
QMediaPlaylist* Playlist::GetCurrentPlayList()
{
    return Playlist::currentPlaylist;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
QMediaPlaylist* Playlist::GetDefaultPlayList()
{
    return  Playlist::defaultPlaylist;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Playlist::LoadDefaultPlayList()
{
    Playlist::allSongs.QStringList::clear();
    Playlist::settingsDir->QDir::setCurrent(QCoreApplication::applicationDirPath() + "/music/");
    Playlist::allSongs = Playlist::settingsDir->QDir::entryList(QStringList() << "*.mp3" << "*.MP3" << "*.wav" << "*.WAV", QDir::Files);
    Playlist::settingsDir->QDir::setCurrent(QCoreApplication::applicationDirPath());

    if(Playlist::CreateDefaultPlaylist(Playlist::defaultPlaylist))
        #ifndef Q_DEBUG
        qDebug() << "loaded default playlist";
        #endif
    else
        #ifndef Q_DEBUG
        qCritical() << "error: can't load default playlist";
        #endif

    return;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Playlist::LoadPlayList(const QString &name)
{
    if(Playlist::LookingForPlayList(name, Playlist::currentPlaylist))
        #ifndef Q_DEBUG
        qDebug() << "loaded playlist";
        #endif
    else
        #ifndef Q_DEBUG
        qCritical() << "error: can't load playlist";
        #endif

    return;
}

//FIX IT!!!!!! INFINITE CYCLE
QStringList Playlist::GetSongsFromCurrentPlayList(const QString &nameOfPlayList)
{
    QStringList songs = {};

    if((nameOfPlayList == "") && (Playlist::CheckSettingsDir() == false))
        return songs;

    const QString path = QCoreApplication::applicationDirPath() + "/bin/" + nameOfPlayList;
    QFile *buffer = new QFile(path);

    qDebug() << path;

    if(buffer->QFile::exists())
    {
        if(buffer->QIODevice::open(QIODevice::ReadOnly))
        {
            QTextStream stream(buffer);

            while(!stream.QTextStream::atEnd())
            {
                qCritical() << "hi";
                songs.QStringList::push_back(stream.QTextStream::readLine().QString::trimmed());
            }

             buffer->QFile::close();
        }
        else
        {
                #ifndef Q_DEBUG
                qCritical() << "error: can't open playlist";
                #endif
        }
    }
    else
    {
        #ifndef Q_DEBUG
        qCritical() << "error: file not exists";
        #endif
    }

    delete buffer;

    return songs;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
QStringList Playlist::GetSongsFromDeaultPlayList()
{
    Playlist::allSongs.QStringList::clear();
    Playlist::settingsDir->QDir::setCurrent(QCoreApplication::applicationDirPath() + "/music/");
    Playlist::allSongs = Playlist::settingsDir->QDir::entryList(QStringList() << "*.mp3" << "*.MP3" << "*.wav" << "*.WAV", QDir::Files);
    Playlist::settingsDir->QDir::setCurrent(QCoreApplication::applicationDirPath());

    return allSongs;
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||METHODS PUBLIC|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||METHODS PRIVATE||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
bool Playlist::CreatePlayList(const QString &name, const QStringList &list)
{
    if((name == "") || (list.QStringList::isEmpty()))
        return false;

    Playlist::CheckSettingsDir();
    Playlist::settingsDir->QDir::setCurrent(QCoreApplication::applicationDirPath());

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

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
bool Playlist::CreateDefaultPlaylist(QMediaPlaylist *medialist)
{
    if(QDir("music").QDir::exists() == false)
        return false;
    else
    {
        medialist->QMediaPlaylist::clear();

        qDebug() << Playlist::allSongs;

        for(const QString &iter : Playlist::allSongs)
        {
            medialist->QMediaPlaylist::addMedia(QMediaContent(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/music/" + iter)));

            #ifndef Q_DEBUG
            qDebug() << iter;
            qDebug() << medialist->QMediaPlaylist::mediaCount();
            #endif
        }

        medialist->setCurrentIndex(1);

        if(medialist->QMediaPlaylist::save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + "default" + ".m3u"), "m3u"))
            return true;
        else
            return false;
    }

}

bool Playlist::SavePlaylist(const QString &name, const QStringList &newListOfSongs, QMediaPlaylist *currentPlaylist)
{
    if(name == "" && newListOfSongs.QStringList::isEmpty())
        return false;

    Playlist::settingsDir->QDir::setCurrent(QCoreApplication::applicationDirPath());
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

    Playlist::settingsDir->QDir::setCurrent(QCoreApplication::applicationDirPath());

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

    Playlist::settingsDir->QDir::setCurrent(QCoreApplication::applicationDirPath());

    if(currentPlaylist->QMediaPlaylist::save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + newName + ".m3u"), "m3u"))
        return true;
    else
        return false;
}

bool Playlist::RenamePlayList(const QString &newName, const QString &currentName)
{
    if((newName == "") && (currentName == ""))
        return false;

    Playlist::settingsDir->QDir::setCurrent(QCoreApplication::applicationDirPath());

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
        Playlist::settingsDir->QDir::mkdir("bin");

        #ifndef Q_DEBUG
        qDebug() << "Folder 'bin' created";
        #endif

        return false;
    }
    else
    {
        #ifndef Q_DEBUG
        qCritical() << "Folder 'bin' already exists!";
        #endif

        return true;
    }
}

bool Playlist::AddSongIntoPlayListByName(const QString &song, const QString &nameOfPlayList, const QString &nameOfCurrentPlayList, const unsigned short int &index)
{
    if((song == "") && (nameOfPlayList == ""))
        return false;

    Playlist::settingsDir->QDir::setCurrent(QCoreApplication::applicationDirPath()); // set default playlist
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

//TEST IT
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

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||METHODS PRIVATE||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
