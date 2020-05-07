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
        Playlist::playlist = new QMediaPlaylist();
    }
    catch (std::bad_alloc &exp)
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
    Playlist::settingsDir->QDir::setCurrent(QCoreApplication::applicationDirPath());
    Playlist::dialog->QFileDialog::setDirectory(QCoreApplication::applicationDirPath() + "/music/");

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
    delete Playlist::playlist;

    return;
}

void Playlist::GetCurrentPlayList()
{

    return;
}

void Playlist::CreateCurrentPlayList(const QString &name)
{
    const QStringList songs = Playlist::dialog->QFileDialog::getOpenFileNames(0, "Create play list", "", "*.mp3 *.wav");

    if(songs.QList::isEmpty())
        return;
    else
        if(Playlist::CreatePlayList(name ,songs, Playlist::playlist))
            qDebug() << "play list success created!" + name;
        else
            qCritical() << "error create play list!" + name;

    return;
}

void Playlist::RemoveCurrentPlayList()
{

    return;
}

bool Playlist::CreatePlayList(const QString &name, const QStringList &list, QMediaPlaylist *medialist)
{
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
    QFile buffer(QCoreApplication::applicationDirPath() + "/bin/" + name + ".bin");

    if(buffer.QFile::remove())
        return true;
    else
        return false;
}

bool Playlist::LookingForPlayList(const QString &name, QMediaPlaylist *medialist)
{
    medialist->QMediaPlaylist::load(QCoreApplication::applicationDirPath() + "/bin/" + name + ".bin");

    if(!medialist->QMediaPlaylist::isEmpty())
        return true;
    else
        return false;
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
