/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
***Created by bogdyname
*/

#include "importmanager.h"

ImportManager::ImportManager()
{
    try
    {
        musicDir = new QDir();
        mp3File = new QFile(this);
        importerWindow = new QFileDialog();
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

    //SETTING UP QtObjects

    //Finder for looking for music
    importerWindow->setDirectory(QDir::rootPath());

    //current path of app
    musicDir->setCurrent(QCoreApplication::applicationDirPath());

    //Check folder of music
    if(musicDir->mkdir("music"))
        qDebug() << "Folder 'music' created";
    else
        qDebug() << "Folder 'music' already exists!";

    return;
}

ImportManager::~ImportManager()
{
    delete musicDir;
    delete importerWindow;

    qDebug() << "Destructor from ImportManager.cpp";
}

void ImportManager::CallFileDialogWithDel()
{
    const QStringList pathOfFiles = importerWindow->getOpenFileNames(0, "Import Music", "", "*.mp3 *.wav *.m4a");

    if(pathOfFiles.isEmpty())
        return;
    else
        SaveFilesIntoMusicFolderAndDeleteIt(pathOfFiles);

    emit this->CallOutToCheckSongsInsideDefaultPlayList();

    return;
}

void ImportManager::CallFileDialogOnlyCopy()
{
    const QStringList pathOfFiles = importerWindow->getOpenFileNames(0, "Import Music", "", "*.mp3 *.wav *.m4a");

    if(pathOfFiles.isEmpty())
        return;
    else
        SaveFilesIntoMusicFolderOnlyCopy(pathOfFiles);

    emit this->CallOutToCheckSongsInsideDefaultPlayList();

    return;
}

void ImportManager::SaveFileViaDragAndDrop(const QStringList &paths)
{
    if(paths.isEmpty())
        return;
    else
        SaveFilesIntoMusicFolderOnlyCopyAfterDrop(paths);

    emit this->CallOutToCheckSongsInsideDefaultPlayList();

    return;
}

const QStringList ImportManager::GetJustAddedSongs()
{
    QStringList buffer = {};

    foreach(const QString &iter, justAddedSongs)
    {
        QString songBuffer = iter;

        //remove unicode char
        songBuffer.remove(-1);

        //add into buffer without current path (just name of song with format) and return it
        buffer.push_back(GetNameOfSongFromCurrentPath(iter));
    }

    return buffer;
}

//Methods for save files
void ImportManager::SaveFilesIntoMusicFolderAndDeleteIt(const QStringList &paths)
{
    for(const QString &iter : paths)
    {
        mp3File->setFileName(iter);

        if(mp3File->open(QFile::ReadOnly))
        {
            const QString nameOfSong = GetNameOfSongFromCurrentPath(iter);

            CheckDir();
            mp3File->copy(iter, musicDir->currentPath() + "/music/" + nameOfSong);
            mp3File->remove();

            #ifndef Q_DEBUG
            qDebug() << "File has been removed: " + iter;
            qDebug() << "Added new file: " + nameOfSong;
            #endif
        }
        else
        {
            #ifndef Q_DEBUG
            qCritical() << "Error open or read file!";
            #endif

            return;
        }

        mp3File->close();
    }

    return;
}

void ImportManager::SaveFilesIntoMusicFolderOnlyCopy(const QStringList &paths)
{
    for(const QString &iter : paths)
    {
        mp3File->setFileName(iter);

        if(mp3File->open(QFile::ReadOnly))
        {
            const QString nameOfSong(GetNameOfSongFromCurrentPath(iter));

            CheckDir();
            mp3File->copy(iter, musicDir->currentPath() + "/music/" + nameOfSong);

            #ifndef Q_DEBUG
            qDebug() << "Added new file: " << musicDir->currentPath() + "/music/" + nameOfSong;
            #endif
        }
        else
        {
            #ifndef Q_DEBUG
            qCritical() << "Error open or read file!";
            #endif

            return;
        }

        mp3File->close();
    }

    return;
}

void ImportManager::SaveFilesIntoMusicFolderOnlyCopyAfterDrop(const QStringList &paths)
{
    justAddedSongs.clear();

    for(const QString &iter : paths)
    {
        //added '/' for UNIX (macOS/Linux)
        QString buffer = "/" + iter;

        //check Windows paths
        QString::const_iterator iterator = buffer.begin() + 2;
        if(*iterator == ":")
            buffer.remove(0, 1);

        mp3File->setFileName(buffer);

        if(mp3File->open(QFile::ReadOnly))
        {
            const QString nameOfSong(GetNameOfSongFromCurrentPath(iter));

            CheckDir();
            mp3File->copy(musicDir->currentPath() + "/music/" + nameOfSong);

            //just added tracks to pass it into playlist
            justAddedSongs.push_back(musicDir->currentPath() + "/music/" + nameOfSong);

            #ifndef Q_DEBUG
            qDebug() << "Added new file: " + musicDir->currentPath() + "/music/" + nameOfSong;
            #endif
        }
        else
        {
            #ifndef Q_DEBUG
            qCritical() << "Error open or read file!";
            #endif

            return;
        }

        mp3File->close();
    }

    return;
}

bool ImportManager::CheckDir()
{
    //current path of app
    musicDir->setCurrent(QCoreApplication::applicationDirPath());

    if(QDir("music").QDir::exists() == false)
    {
        musicDir->mkdir("music");

        #ifndef Q_DEBUG
        qDebug() << "Folder 'music' created";
        #endif

        return false;
    }
    else
    {
        #ifndef Q_DEBUG
        qCritical() << "Folder 'music' already exists!";
        #endif

        return true;
    }
}

QString ImportManager::GetNameOfSongFromCurrentPath(const QString nameOfSong)
{
    QString::const_iterator iter = nameOfSong.end();
    QString buffer = "";

    if(*iter == NULL)
        iter = nameOfSong.end() - 1;

    for(; iter != nameOfSong.begin(); --iter)
    {
            //unix like         //windows
        if((*iter == "/") || (*iter == "\\"))
            return buffer;
        else
            buffer.push_front(*iter);
    }

    return buffer;
}
