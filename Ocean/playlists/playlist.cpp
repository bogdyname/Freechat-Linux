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
        Playlist::track = new QFile();
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
    delete Playlist::track;
    delete Playlist::dialog;
    delete Playlist::playlist;

    return;
}

void Playlist::GetCurrentPlayList()
{

    return;
}

void Playlist::CreateCurrentPlayList()
{
    const QStringList songs = Playlist::dialog->QFileDialog::getOpenFileNames(0, "Create play list", "", "*.mp3 *.wav");

    if(songs.QList::isEmpty())
        return;
    else
        if(Playlist::CreatePlayList(songs, Playlist::playlist))
            qDebug() << "play list success created!";
        else
            qCritical() << "error create play list!";

    return;
}

void Playlist::RemuveCurrentPlayList()
{

    return;
}

bool Playlist::CreatePlayList(const QStringList &list, QMediaPlaylist *medialist)
{
    Playlist::CheckSettingsDir();

    if(Playlist::track->QFile::open(ReadOnly))
    {
        Playlist::track->QFile::setFileName("playlists.bin");//TTS
        QTextStream stream(Playlist::track);//TTS

        for(const QString &iter : list)
        {
            stream << iter << '\n';//write song into file for save it //TTS
            medialist->addMedia(QMediaContent(QUrl::fromLocalFile(iter)));//add song into playlist
        }

        Playlist::track->QFile::close();

        return true;
    }
    else
    {
        #ifndef Q_DEBUG
        qCritical() << "Error open or read file!";
        #endif

        return false;
    }
}

bool SavePlayListIntoFile();
bool RemuvePlayListFromFile();
bool LookingForListInFile();

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
