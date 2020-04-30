/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#include "importmanager.h"

ImportManager::ImportManager()
{
    try
    {
        ImportManager::musicDir = new QDir();
        ImportManager::mp3File = new QFile();
        ImportManager::importerWindow = new QFileDialog();//TTS CODE LIKE EXAMPLE FOR Ocean.cpp
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
    ImportManager::musicDir->QDir::setCurrent(QCoreApplication::applicationDirPath());

    //Check folder of music
    if(ImportManager::musicDir->QDir::mkdir("music"))
        qDebug() << "good";
    else
        qDebug() << "not good";

     //TTS CODE LIKE EXAMPLE FOR Ocean.cpp
    //Finder for looking for music
    ImportManager::importerWindow->QFileDialog::setDirectory(QDir::rootPath());

    //TTS CODE LIKE EXAMPLE FOR Ocean.cpp
    //TTS FOR ONE FILE
   QString path = importerWindow->getOpenFileName(0, "TTS", "", "*.jpg");

    if(path.QString::isEmpty())
       return;
    else
        SaveFileIntoMusicFolder(path);
    //TTS FOR ONE FILE

    //TTS FOR MORE FILES
//    QStringList pathOfFiles = importerWindow->getOpenFileNames(0, "TTS", "", "*.jpg");

//    if(pathOfFiles.QStringList::isEmpty())
//        return;
//    else
//        SaveFilesIntoMusicFolder(pathOfFiles);
    //TTS FOR MORE FILES
}

ImportManager::~ImportManager()
{
    delete ImportManager::musicDir;
    delete ImportManager::mp3File;
    delete ImportManager::importerWindow;
}

//Slots for save files
void ImportManager::SaveFileIntoMusicFolder(const QString &pathOfmp3)
{
    //Check path of file
    if(!pathOfmp3.isEmpty())
        ImportManager::mp3File->QFile::setFileName(pathOfmp3);
    else
        return;

    //copy file into music folder there is folder of app and delete it
    if(ImportManager::mp3File->QFile::open(QIODevice::ReadOnly))
    {
        const QString nameOfSong = ImportManager::GetNameOfSongFromCurrentPath(pathOfmp3);

        ImportManager::CheckDir();
        ImportManager::mp3File->QFile::copy(pathOfmp3, ImportManager::musicDir->QDir::currentPath() + "/music/" + nameOfSong);
        ImportManager::mp3File->QFile::remove();

        #ifndef Q_DEBUG
        qDebug() << "File has been removed: " + pathOfmp3;
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

    ImportManager::mp3File->close();

    return;
}

void ImportManager::SaveFilesIntoMusicFolder(const QStringList &pathsOfmp3)
{
    if(pathsOfmp3.QStringList::isEmpty())
        return;

    for(const auto &iter : pathsOfmp3)
    {
        ImportManager::mp3File->QFile::setFileName(iter);

        if(ImportManager::mp3File->QFile::open(QIODevice::ReadOnly))
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

        ImportManager::mp3File->close();
    }

    return;
}

bool ImportManager::CheckDir()
{
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

QString ImportManager::GetNameOfSongFromCurrentPath(const QString nameOfSong)
{
    QString::const_iterator iter = nameOfSong.QString::end();
    QString buffer = "";

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
