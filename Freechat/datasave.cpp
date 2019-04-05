/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "username.h"
#include "datasave.h"
#include "freechat.h"
#include "duinterface.h"
#include "usernametable.h"

Datasave::Datasave(QObject *parent)
    : QSaveFile(parent)
{
    connect(QMessageBox::information, SIGNAL(CheckYourMemorySize()),
            this, SLOT(AbortProgWheneverMemorySizeFull()));
    connect(    , SIGNAL(),
            this, SLOT());
}

bool Datasave::SaveFile()
{
    saveFileVariable = (UserSelect() == "YES");

    return 0;
}

bool Datasave::DeleteFile()
{
    deleteFileVariable = (UserSelect() == "YES");

    return 0;
}

QFile Datasave::DataWriterInFile(QFile &fileWithData)
{
    fileWithData = ;

}
