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
        ImportManager::importerWindow = new QFileDialog();
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

    //Finder for looking for music
    ImportManager::importerWindow->QFileDialog::setDirectory(QDir::rootPath());

    //SIGNALS WITH SLOTS
    //looking for file and save if into own folder
    QObject::connect(ImportManager::importerWindow, SIGNAL(fileSelected(const QString)), this, SLOT(SaveFileIntoMusicFolder(const QString)));
    QObject::connect(ImportManager::importerWindow, SIGNAL(filesSelected(QStringList)), this, SLOT(SaveFilesIntoMusicFolder(QStringList)));


    //TTS
    QString path = importerWindow->getOpenFileName(0, "TTS", "", "*.jpg");

    if(path.isEmpty())
        return;
    else
        SaveFileIntoMusicFolder(path);
    //TTS
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
        ImportManager::CheckDir();

        //Need to rework it for save by only last name of the file (like this -> "I see fire.mp3")
        //For this case need to sort out the string of current path of file
        ImportManager::mp3File->QFile::copy(pathOfmp3, ImportManager::musicDir->QDir::currentPath() + "/music/" + "photo.jpg");
        ImportManager::mp3File->QFile::remove();

        #ifndef Q_DEBUG
        qDebug() << "File has been removed: " + pathOfmp3;
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
