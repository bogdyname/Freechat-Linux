/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
***Created by bogdyname
*/

#include "importmanager.h"


/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||MAIN|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
ImportManager::ImportManager(QObject *parent)
    : QFile(parent)
{
    try
    {
        cd = new QDir();
        mp3File = new QFile(this);
        importerWindow = new QFileDialog();
    }
    catch(...)
    {
        qCritical() << "Some exception caught";
        exit(1);
    }

    //Singals with orivate Slots
    connect(this, &ImportManager::CallOutToExportTracksOfPlayList, this, &ImportManager::ExportTracksOfPlayList);

    //SETTING UP QtObjects
    //Finder for looking for music
    importerWindow->setDirectory(QDir::rootPath());

    //current path of app
    cd->setCurrent(QCoreApplication::applicationDirPath());

    //Check folder of music
    cd->mkdir("music");

    return;
}

ImportManager::~ImportManager()
{
    delete cd;
    delete importerWindow;

    qDebug() << "Destructor from ImportManager.cpp";
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||MAIN|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||SLOTS PUBLIC|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
void ImportManager::CallFileDialogWithDel()
{
    //list with paths of files (get via QFileDialog)
    const QStringList pathOfFiles = importerWindow->getOpenFileNames(0, "Import Music", "", "*.mp3 *.wav *.m4a *.flac");

    //close method if list is empty
    if(pathOfFiles.isEmpty())
        return;
    else//save files inside app and delete from getted path
        SaveFilesIntoMusicFolderAndDeleteIt(pathOfFiles);

    //call methods to check playlist 'all' (reboot playlist)
    emit this->CallOutToCheckSongsInsideDefaultPlayList();

    return;
}

void ImportManager::CallFileDialogOnlyCopy()
{
    //list with paths of files (get via QFileDialog)
    const QStringList pathOfFiles = importerWindow->getOpenFileNames(0, "Import Music", "", "*.mp3 *.wav *.m4a *.flac");

    //close method if list is empty
    if(pathOfFiles.isEmpty())
        return;
    else//copy files into app
        SaveFilesIntoMusicFolderOnlyCopy(pathOfFiles);

    //call methods to check playlist 'all' (reboot playlist)
    emit this->CallOutToCheckSongsInsideDefaultPlayList();

    return;
}

void ImportManager::SaveFileViaDragAndDrop(const QStringList &paths)
{
    //close method if list is empty
    if(paths.isEmpty())
        return;
    else//copy files into app
        SaveFilesIntoMusicFolderOnlyCopyAfterDrop(paths);

    //call methods to check playlist 'all' (reboot playlist)
    emit this->CallOutToCheckSongsInsideDefaultPlayList();

    return;
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||SLOTS PUBLIC|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||SLOTS PRIVATE||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
void ImportManager::ExportTracksOfPlayList(const QString &playlist)
{
    if(playlist == "")
        return; 

    //get folder via QFileDialog to export files
    const QString pathToExport = importerWindow->getExistingDirectory(0, "Export Music", "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    //set path to export files
    cd->setCurrent(pathToExport);
    cd->mkdir("export music");
    //path (with dir) to copy files from app
    const QString pathOfExportDir = pathToExport + "/export music/";

    //parse file
    QFile *buffer = new QFile(QCoreApplication::applicationDirPath() + "/bin/" + playlist + ".m3u8");
    QFile *bufferOfPath = new QFile();
    QTextStream stream(buffer);
    QString pathOfTrack = "";
    QString nameOfSong = "";

    if(buffer->open(QIODevice::ReadOnly))
    {
        // read specific line by index
        while(!stream.atEnd())
        {
            //read line with path of track
            pathOfTrack = stream.readLine().trimmed();

            //added path into buffer to copy it via QFile::copy()
            QString buffer = pathOfTrack;

            //path of file with unicode
            buffer.remove(0, 8);
            //added '/' for UNIX (macOS/Linux)
            buffer.push_front("/");

            //check Windows paths
            QString::const_iterator iterator = buffer.begin() + 2;
            if(*iterator == ":")
                buffer.remove(0, 1);

            //remove first 8 elements 'file:///'
            ParseStringToRemoveFirstChars(pathOfTrack);
            //parsing all path to get only names of files
            nameOfSong = GetNameOfSongFromCurrentPath(buffer);

            //copy into export dir
            bufferOfPath->copy(buffer, pathOfExportDir + nameOfSong);
        }

        delete buffer;
        delete bufferOfPath;
    }
    else
    {
        delete buffer;
        delete bufferOfPath;
    }

    cd->setCurrent(QCoreApplication::applicationDirPath());

    return;
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||SLOTS PRIVATE||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||METHODS PUBLIC|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
const QStringList ImportManager::GetJustAddedSongs()
{
    //list for path - just added files via Drag and Drop
    QStringList buffer = {};

    //parsing to remove last char 'UNICODE'
    foreach(const QString &iter, justAddedSongs)
    {
        //copy current file path
        QString songBuffer = iter;

        //remove unicode char
        songBuffer.remove(-1);

        //add into buffer without current path (just name of song with format) and return it
        buffer.push_back(GetNameOfSongFromCurrentPath(iter));
    }

    return buffer;
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||METHODS PUBLIC|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||METHODS PRIVATE||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
//Methods for save files
void ImportManager::SaveFilesIntoMusicFolderAndDeleteIt(const QStringList &paths)
{
    //parsing list with paths
    for(const QString &iter : paths)
    {
        //pointer on current file
        mp3File->setFileName(iter);

        if(mp3File->open(QFile::ReadOnly))
        {
            //get name from full path
            const QString nameOfSong = GetNameOfSongFromCurrentPath(iter);

            //check dir of app
            CheckDir();
            //add files into app
            mp3File->copy(iter, cd->currentPath() + "/music/" + nameOfSong);
            //delete file from full path
            mp3File->remove();
        }
        else
        {
            //clear last point
            mp3File = nullptr;

            return;
        }

        mp3File->close();
    }

    //clear last point
    mp3File = nullptr;

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
            mp3File->copy(iter, cd->currentPath() + "/music/" + nameOfSong);
        }
        else
            return;

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
            mp3File->copy(cd->currentPath() + "/music/" + nameOfSong);

            //just added tracks to pass it into playlist
            justAddedSongs.push_back(cd->currentPath() + "/music/" + nameOfSong);
        }
        else
            return;

        mp3File->close();
    }

    return;
}

bool ImportManager::CheckDir()
{
    //current path of app
    cd->setCurrent(QCoreApplication::applicationDirPath());

    if(QDir("music").QDir::exists() == false)
    {
        cd->mkdir("music");

        return false;
    }
    else
        return true;
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

void ImportManager::ParseStringToRemoveFirstChars(QString &string)
{
    string.remove(0, 8);
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||METHODS PRIVATE||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
