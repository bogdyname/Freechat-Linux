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

//SLOTS
void Playlist::CreateCurrentPlayList(const QString &name)
{
    if(name == "")
        return;

    const QStringList songs = Playlist::dialog->QFileDialog::getOpenFileNames(0, "Create play list", "", "*.mp3 *.wav");

    if(songs.QList::isEmpty())
        return;
    else
        if(Playlist::CreatePlayList(name, songs, Playlist::currentPlaylist))
            #ifndef Q_DEBUG
            qDebug() << "play list successed created!" + name;
            #endif
        else
            #ifndef Q_DEBUG
            qCritical() << "error create play list!" + name;
            #endif

    return;
}

void Playlist::RemoveCurrentPlayList(const QString &name)
{
    if(name == "")
        return;

    if(Playlist::RemovePlayList(name))
        #ifndef Q_DEBUG
        qDebug() << "playlist successed removed: " << name;
        #endif
    else
        #ifndef Q_DEBUG
        qCritical() << "error: can't remove playlist";
        #endif

    return;
}

//Methods
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

bool Playlist::CreatePlayList(const QString &name, const QStringList &list, QMediaPlaylist *medialist)
{
    if((name == "") || (!list.QStringList::isEmpty()))
        return false;

    Playlist::CheckSettingsDir();

    for(const QString &iter : list)
        medialist->QMediaPlaylist::addMedia(QMediaContent(QUrl::fromLocalFile(iter)));//add song into playlist

    if(medialist->QMediaPlaylist::save(QCoreApplication::applicationDirPath() + "/bin/" + name, ".bin"))
        return true;
    else
        return false;
}

bool Playlist::RemovePlayList(const QString &name)
{
    if(name == "")
        return false;

    Playlist::CheckSettingsDir();

    QFile buffer(QCoreApplication::applicationDirPath() + "/bin/" + name + ".bin");

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
    medialist->QMediaPlaylist::load(QCoreApplication::applicationDirPath() + "/bin/" + name + ".bin");
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
