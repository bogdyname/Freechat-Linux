/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
***Created by bogdyname
*/

#include "playlist.h"

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
     * Rename -------------------------
        2.1) rename current playlist
        2.2) rename selected playlist
     * Name ---------------------------
        3.1) set name of current playlist (playlist 'all' too!)
     * Create -------------------------
        4.1) create new playlist
     * Remove -------------------------
        5.1) remove playlist by name
    */
    //Save
    QObject::connect(this, &Playlist::CallOutSaveCurrentPlayList, this, &Playlist::SaveCurrentPlayList);
    QObject::connect(this, &Playlist::CallOutSaveSelectedPlayList, this, &Playlist::SaveSelectedPlayList);
    //Rename
    QObject::connect(this, &Playlist::CallOutRenameCurrentPlayList, this, &Playlist::RenameCurrentPlayList);
    QObject::connect(this, &Playlist::CallOutRenameSelectedPlayList, this, &Playlist::RenameSelectedPlayList);
    //Name
    QObject::connect(this, &Playlist::CallOutSetCurrentPlayListName, this, &Playlist::SetCurrentPlayListName);
    //Create
    QObject::connect(this, &Playlist::CallOutCreateNewPlayList, this, &Playlist::CreateNewPlayList);
    //Remove
    QObject::connect(this, &Playlist::CallOutRemovePlayListByName, this, &Playlist::RemovePlayListByName);

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

//SLOTS public
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

//Methods public
QString Playlist::GetCurrentPlayListName()
{
    return Playlist::currentPlaylistName;
}

QMediaPlaylist* Playlist::GetCurrentPlayList()
{
    return Playlist::currentPlaylist;
}

QMediaPlaylist* Playlist::GetDefaultPlayList()
{
    return  Playlist::defaultPlaylist;
}

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

//Methods private
bool Playlist::CreatePlayList(const QString &name, const QStringList &list)
{
    if((name == "") || (!list.QStringList::isEmpty()))
        return false;

    Playlist::CheckSettingsDir();
    Playlist::settingsDir->QDir::setCurrent(QCoreApplication::applicationDirPath());

    QMediaPlaylist *bufferPlaylist = new QMediaPlaylist();

    for(const QString &iter : list)
        bufferPlaylist->QMediaPlaylist::addMedia(QMediaContent(QUrl::fromLocalFile(iter)));//add song into playlist

    if(bufferPlaylist->QMediaPlaylist::save(QCoreApplication::applicationDirPath() + "/bin/" + name, ".m3u"))
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
    medialist->QMediaPlaylist::load(QCoreApplication::applicationDirPath() + "/bin/" + name + ".m3u");
    medialist->setCurrentIndex(1);

    if(!medialist->QMediaPlaylist::isEmpty())
        return true;
    else
        return false;
}

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

        return true;
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

    if(currentPlaylist->QMediaPlaylist::save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + name), ".m3u"))
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

    if(bufferPlaylist->QMediaPlaylist::save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + name), ".m3u"))
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

    if(currentPlaylist->QMediaPlaylist::save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + newName), ".m3u"))
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
    bufferPlaylist->QMediaPlaylist::load(QCoreApplication::applicationDirPath() + "/bin/" + currentName + ".m3u");

    if(bufferPlaylist->QMediaPlaylist::save(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/bin/" + newName), ".m3u"))
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
