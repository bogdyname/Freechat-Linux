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
        ImportManager::mp3 = new QFile();
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

    ImportManager::importerWindow->QFileDialog::setDirectory(QDir::rootPath());

    //SIGNALS WITH SLOTS
    //looking for file and save if into own folder
    QObject::connect(ImportManager::importerWindow, SIGNAL(fileSelected(QString)), this, SLOT(SaveFileIntoMusicFolder(QString)));
}

ImportManager::~ImportManager()
{
    delete ImportManager::mp3;
    delete ImportManager::importerWindow;
}

void ImportManager::SaveFileIntoMusicFolder(const QString &pathOfmp3)
{
    ImportManager::mp3->setFileName(pathOfmp3);

    return;
}
