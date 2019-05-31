/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/


##include "username.h"
#include "datasave.h"
#include "freechat.h"
#include "usernametable.h"

Datasave::Datasave(QObject *parent)
    : QFile(parent)
{
   connect( , SIGNAL(RunTimeIsOver()),
            this, SLOT(RunBackupFiles()));
   connect( , SIGNAL(SaveDataFileAs()),
            this, SLOT(Datasave()));
   connect( , SIGNAL(CheckYourMemorySize()),
            this, SLOT(DeleteAllDataForFreeMemory()));
   connect( , SIGNAL(ReadFileForViewMessages()),
            this, SLOT(ReadFile()));
   connect( , SIGNAL(CheckUsernameForSaveFile()),
            this, SLOT(Datasave()));


   fileWithData.setFileName("data.txt");
   fileWithDataForBackup.setFileName("backupdata.txt");

   if((CheckForFileExists() == true) && (CheckForFileIsOpen() == true))
   {
        if(fileWithData.open(WriteOnly))
        {
            fileWithData.write("NAME OF USER");
            fileWithData.write("WRITE FROM TEXT FIELD WIDGET!!");
            fileWithData.flush();
        }
        else
        {
            /*clear code*/
        }
   }
}

bool Datasave::CheckForFileExists()
{
    if(exists("data.txt"))
    {
        return true;
    }
    else
    {
         /*clear code*/
    }
}

bool Datasave::CheckForFileIsOpen()
{
    if(fileWithData.isOpen())
    {
        return true;
    }
    else
    {
         /*clear code*/
    }
}

void Datasave::CheckUsernameForSaveFile()
{

    return;
}

void Datasave::SaveDataFileAs()
{

    return;
}

void Datasave::CheckYourMemorySize()
{
    qDebug() << storage.rootPath();

    if (storage.isReadOnly())
    {
        qDebug() << "isReadOnly:" << storage.isReadOnly();
    }
    else
    {
        /*clear code*/
    }

    qDebug() << "name:" << storage.name();
    qDebug() << "fileSystemType:" << storage.fileSystemType();
    qDebug() << "size:" << storage.bytesTotal()/1000/1000 << "MB";
    qDebug() << "availableSize:" << storage.bytesAvailable()/1000/1000 << "MB";

    if (storage.bytesFree() == 1)
    {
        QMessageBox::information(this, tr("WARNING!"),
                        tr("Check your memory size!"));
    }
    else
    {
        /*clear code*/
    }

    return;
}

void Datasave::DeleteAllDataForFreeMemory()
{
    QFile("data.txt").remove();
    QFile("backupdata.txt").remove();

    return;
}

void Datasave::RunTimeIsOver()
{


    return;
}

void Datasave::RunBackupFiles()
{
    if((fileWithData.open(ReadOnly)) && (fileWithDataForBackup.open(WriteOnly)))
    {
        block = fileWithData.readAll();
        fileWithDataForBackup.write(block);
        fileWithData.close();
        fileWithDataForBackup.flush();
    }
    else
    {
        /*clear code*/
    }

    return;
}

void Datasave::ReadFileForViewMessages()
{


    return;
}

void Datasave::ReadFile()
{
    if ((fileWithData.exists()) && (fileWithData.open(ReadOnly)))
    {
        (fileWithData.readAll());
        fileWithData.close();
    }
    else
    {
        /*clear code*/
    }

    return;
}
