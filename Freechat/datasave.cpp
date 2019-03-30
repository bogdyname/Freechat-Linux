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

}

bool Datasave::SaveFile()
{
    saveFileVariable = (UserSelect() == "YES");

    return true;
}

bool Datasave::DeleteFile()
{
    deleteFileVariables = (UserSelect() == "YES");

    return true;
}

QFile Datasave::DataWriterInFile()
{


    return ;
}
