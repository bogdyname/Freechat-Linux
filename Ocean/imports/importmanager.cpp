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
        ImportManager::musicDir = new QDir();
        ImportManager::mp3File = new QFile();
        ImportManager::importerWindow = new QFileDialog();
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
    ImportManager::importerWindow->QFileDialog::setDirectory(QDir::rootPath());

    //current path of app
    ImportManager::musicDir->QDir::setCurrent(QCoreApplication::applicationDirPath());

    //Check folder of music
    if(ImportManager::musicDir->QDir::mkdir("music"))
        qDebug() << "Folder 'music' created";
    else
        qDebug() << "Folder 'music' already exists!";

    return;
}

ImportManager::~ImportManager()
{
    delete ImportManager::musicDir;
    delete ImportManager::mp3File;
    delete ImportManager::importerWindow;
}

void ImportManager::CallFileDialogWithDel()
{
    const QStringList pathOfFiles = ImportManager::importerWindow->QFileDialog::getOpenFileNames(0, "Import Music", "", "*.mp3 *.wav *.m4a");

    if(pathOfFiles.QStringList::isEmpty())
        return;
    else
        ImportManager::SaveFilesIntoMusicFolderAndDeleteIt(pathOfFiles);

    emit this->ImportManager::CallOutToCheckSongsInsideDefaultPlayList();

    return;
}

void ImportManager::CallFileDialogOnlyCopy()
{
    const QStringList pathOfFiles = ImportManager::importerWindow->QFileDialog::getOpenFileNames(0, "Import Music", "", "*.mp3 *.wav *.m4a");

    if(pathOfFiles.QStringList::isEmpty())
        return;
    else
        ImportManager::SaveFilesIntoMusicFolderOnlyCopy(pathOfFiles);

    emit this->ImportManager::CallOutToCheckSongsInsideDefaultPlayList();

    return;
}

void ImportManager::DeleteMusicFromApp(const QString &song)
{
    if(ImportManager::DeleteMusic(song))
        qDebug() << "all music delete";
    else
        qDebug() << "error: can't delete";

    return;
}

void ImportManager::DeleteAllMusicFromApp()
{
    if(ImportManager::DeleteAllMusic())
        qDebug() << "all music delete";
    else
        qDebug() << "error: can't delete";

    return;
}

//Methods for save files
void ImportManager::SaveFilesIntoMusicFolderAndDeleteIt(const QStringList &pathsOfmp3)
{
    for(const QString &iter : pathsOfmp3)
    {
        ImportManager::mp3File->QFile::setFileName(iter);

        if(ImportManager::mp3File->QFile::open(QFile::ReadOnly))
        {
            const QString nameOfSong = ImportManager::GetNameOfSongFromCurrentPath(iter);

            ImportManager::CheckDir();
            ImportManager::mp3File->QFile::copy(iter, ImportManager::musicDir->QDir::currentPath() + "/music/" + nameOfSong);
            ImportManager::mp3File->QFile::remove();

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

        ImportManager::mp3File->QFile::close();
    }

    return;
}

void ImportManager::SaveFilesIntoMusicFolderOnlyCopy(const QStringList &pathsOfmp3)
{
    for(const QString &iter : pathsOfmp3)
    {
        ImportManager::mp3File->QFile::setFileName(iter);

        if(ImportManager::mp3File->QFile::open(QFile::ReadOnly))
        {
            const QString nameOfSong(ImportManager::GetNameOfSongFromCurrentPath(iter));

            ImportManager::CheckDir();
            ImportManager::mp3File->QFile::copy(iter, ImportManager::musicDir->QDir::currentPath() + "/music/" + nameOfSong);

            #ifndef Q_DEBUG
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

        ImportManager::mp3File->QFile::close();
    }

    return;
}

bool ImportManager::CheckDir()
{
    //current path of app
    ImportManager::musicDir->QDir::setCurrent(QCoreApplication::applicationDirPath());

    if(QDir("music").QDir::exists() == false)
    {
        ImportManager::musicDir->QDir::mkdir("music");

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

bool ImportManager::DeleteMusic(const QString &song)
{
    try
    {
        QFile *bufferMP3 = new QFile(QCoreApplication::applicationDirPath() + "/music/" + song + ".mp3");
        QFile *bufferWAV = new QFile(QCoreApplication::applicationDirPath() + "/music/" + song + ".wav");
        QFile *bufferM4A = new QFile(QCoreApplication::applicationDirPath() + "/music/" + song + ".m4a");

        bufferMP3->QFile::remove();
        bufferWAV->QFile::remove();
        bufferM4A->QFile::remove();

        delete bufferMP3;
        delete bufferWAV;
        delete bufferM4A;

        return true;
    }
    catch(...)
    {
        qDebug() << "error: can't remove song from app - " << song;

        return false;
    }
}

bool ImportManager::DeleteAllMusic()
{
    QStringList allSongs = ImportManager::musicDir->QDir::entryList(QStringList() << "*.mp3" << "*.MP3" << "*.wav" << "*.WAV" << "*.m4a" << "*.M4A", QDir::Files);

    if(!allSongs.QList::isEmpty())
    {
        try
        {
            QFile *bufferMP3 = new QFile();
            QFile *bufferWAV = new QFile();
            QFile *bufferM4A = new QFile();

            for(const QString &iterForAllSongs : allSongs)
            {
                bufferMP3->QFile::remove(QCoreApplication::applicationDirPath() + "/music/" + iterForAllSongs + ".mp3");
                bufferWAV->QFile::remove(QCoreApplication::applicationDirPath() + "/music/" + iterForAllSongs + ".wav");
                bufferM4A->QFile::remove(QCoreApplication::applicationDirPath() + "/music/" + iterForAllSongs + ".m4a");
            }

            delete bufferMP3;
            delete bufferWAV;
            delete bufferM4A;

            return true;
        }
        catch(...)
        {
            qDebug() << "error: can't remove all music";
        }
    }

    return false;
}

QString ImportManager::GetNameOfSongFromCurrentPath(const QString nameOfSong)
{
    QString::const_iterator iter = nameOfSong.QString::end();
    QString buffer = "";

    if(*iter == NULL)
        iter = nameOfSong.QString::end() - 1;

    for(; iter != nameOfSong.QString::begin(); --iter)
    {
            //unix like         //windows
        if((*iter == "/") || (*iter == "\\"))
            return buffer;
        else
            buffer.QString::push_front(*iter);
    }

    return buffer;
}
