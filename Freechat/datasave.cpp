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
   // connect( , SIGNAL(CheckYourMemorySize()),
     //       this, SLOT(AbortProgWheneverMemorySizeFull()));
   // connect(    , SIGNAL(CheckUsernameFOrSaveFile()),
     //       this, SLOT(SveFileForUsername()));
}

bool Datasave::SaveFile()
{

}

bool Datasave::DeleteFile()
{

}

QFile Datasave::DataWriterInFile(QFile &fileWithData)
{

}

void Datasave::CheckUsernameForSaveFile()
{

}

void Datasave::SaveFileForUsername()
{

}

void Datasave::CheckYourMemorySize()
{
    /*
    if (listWithDataSave->count()-> == 1)
    {
        QMessageBox::information(this, tr("WARNING!"),
                        tr("Check your memory size!"));
    }
    else
    {
        /*CLEAR CODE
    }
   */
}
