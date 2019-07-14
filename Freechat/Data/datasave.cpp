/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Data/datasave.h"

Datasave::Datasave(Freechat *parent)
    : QFile(parent)
{
   connect( , SIGNAL(RunTimeIsOver()),
            this, SLOT(RunBackupFiles()));
   connect( , SIGNAL(CheckYourMemorySize()),
            this, SLOT(DeleteAllDataForFreeMemory()));
   connect( , SIGNAL(ReadFileForViewMessages()),
            this, SLOT(ReadFile()));
   connect( , SIGNAL(CheckIpAddressForSaveFile()),
            this, SLOT());

   QString fname = "filewd" +
           QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss") + ".txt";
   QFile file(fname);

   /*CHECK THIS SIDE!*/
   QString str;
   PassOnWANIp(str);
  /*CHECK THIS SIDE!*/

   if(buffer != nullptr)
   {
       buffer = new QByteArray;

       if((file.exists()) && (file.isOpen()))
       {
            if(file.open(WriteOnly))
            {
                QTextStream writeStream(&file);
                writeStream << "messeges";
                file.write(*buffer);
                file.flush();
            }
            else
            {
                file.close();
            }
        }
        else
        {
            /*clear code*/
        }
   }

   QDir().mkdir(QApplication::applicationDirPath()+"/../savedata");
}

Datasave::Datasave(QFile &fileWithData, QFile &fileWithDataForBackup)
{
    if(buffer != nullptr)
    {
        buffer = new QByteArray;

        if((fileWithData.open(ReadOnly)) && (fileWithDataForBackup.open(WriteOnly)))
        {
            *buffer = fileWithData.readAll();
            fileWithDataForBackup.write(*buffer);
            fileWithData.close();
            fileWithDataForBackup.flush();
        }
        else
        {
            fileWithData.close();
            fileWithDataForBackup.flush();
        }
    }
    else
    {
        /*clear code*/
    }
}

Datasave::~Datasave()
{
    delete runTimer;
    delete buffer;
}

inline void Datasave::CheckIpAddressForSaveFile()
{
    QString str;
    PassOnWANIp(str);

    if(/*user here make operator*/)
    {

    }
    else
    {
        /*clear code*/
    }

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

inline void Datasave::DeleteAllDataForFreeMemory(QFile &fileWithData, QFile &fileWithDataForBackup)
{
    fileWithData.remove();
    fileWithDataForBackup.remove();

    return;
}

inline void Datasave::RunTimeIsOver()
{


    return;
}

void Datasave::ReadFileForViewMessages()
{


    return;
}

inline void Datasave::ReadFile(QFile &fileWithData)
{
    if ((fileWithData.exists()) && (fileWithData.open(ReadOnly)))
    {
        ui->textFieldForViewMessages->setText(fileWithData.readAll());
        fileWithData.close();
    }
    else
    {
        /*clear code*/
    }

    return;
}
