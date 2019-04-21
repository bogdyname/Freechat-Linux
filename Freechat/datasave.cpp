/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "username.h"
#include "datasave.h"
#include "freechat.h"
#include "usernametable.h"

Datasave::Datasave(QObject *parent)
    : QSaveFile(parent)
{
   connect( , SIGNAL(CheckYourMemorySize()),
            this, SLOT(AbortProgWheneverMemorySizeFull()));
   connect(    , SIGNAL(CheckUsernameFOrSaveFile()),
            this, SLOT(SveFileForUsername()));
   connect(    , SIGNAL(RunTimeIsOver()),
            this, SLOT(RunBackupFiles()));
}

bool Datasave::SaveFile()
{
    if((DataWriterInFile().exists())&&(DataWriterInFile().open(ReadOnly)))
    {
        QString str = "";
        while(!DataWriterInFile().atEnd())
        {
            str += DataWriterInFile().readLine();
        }
        ui->textBrowser->setText(str);
        DataWriterInFile().close();
    }
    else
    {
        /*clear code*/
    }
}

bool Datasave::DeleteFile()
{

}

QFile Datasave::DataWriterInFile(QFile &fileWithData)
{
    if(fileWithData.open(WriteOnly))
    {
        fileWithData.write("NAME OF USER");
        fileWithData.write("WRITE FROM FIELD WIDGET!!");
        fileWithData.close();
    }
    else
    {
        /*clear code*/
    }
}

void Datasave::CheckUsernameForSaveFile()
{

}

void Datasave::SaveFileForUsername()
{

}

void Datasave::CheckYourMemorySize()
{

    if (listWithDataSave->count()-> == 1)
    {
        QMessageBox::information(this, tr("WARNING!"),
                        tr("Check your memory size!"));
    }
    else
    {
        /*clear code*/
    }

}

void Datasave::RunTimeIsOver()
{

}

void Datasave::RunBackupFiles()
{

}
