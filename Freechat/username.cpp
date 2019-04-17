/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "username.h"
#include "datasave.h"
#include "usernametable.h"


Username::Username(QObject *parent)
    : QFile(parent)
{
    /*
    connect(QMessageBox::   , SIGNAL(AskUserForReadContactName()),
            this, SLOT(FileForWritingIpAddress(const QString &name)));
    connect(QMessageBox::   , SIGNAL(AskUserForReadContactName()),
            this, SLOT(FileForWritingMACAddress(const QString &name)));
    connect(QMessageBox::   , SIGNAL(AskUserForWriteContactName()),
            this, SLOT(FileForReadingIpAddress(const QString &fileName, const QString &newName);));
    connect(QMessageBox::   , SIGNAL(AskUserForWriteContactName()),
            this, SLOT(FileForReadingMACAddress(const QString &fileName, const QString &newName);));

    connect(QMessageBox::   , SIGNAL(MessegBoxWithCheckingCorrectReadContactName()),
            this, SLOT(CheckingCorrectReadIpddress()));
    connect(QMessageBox::   , SIGNAL(MessegBoxWithCheckingCorrectReadContactName()),
            this, SLOT(CheckingCorrectReadMACddress()));
    connect(QMessageBox::   , SIGNAL(MessegBoxWithCheckingCorrectWriteContactName),
            this, SLOT(CheckingCorrectWriteIpddress()));
    connect(QMessageBox::   , SIGNAL(MessegBoxWithCheckingCorrectWriteContactName),
            this, SLOT(CheckingCorrectWriteMACddress()));
            */
}

/*

bool Username::AskUserForReadContactName()
{
    //QMessageBox::ask(this, tr("Read contact"),
    //tr("Do you want to read this contact?"));
}

bool Username::AskUserForWriteContactName()
{
    //QMessageBox::ask(this, tr("Write contact"),
    //tr("Do you want to write this contact?"));
}

bool Username::MessegBoxWithCheckingCorrectReadContactName()
{

}

bool Username::MessegBoxWithCheckingCorrectWriteContactName()
{

}

QFile Username::FileForWritingIpAddress(const QString &name)
{

}

QFile Username::FileForWritingMACAddress(const QString &name)
{

}

QFile Username::FileForReadingIpAddress(const QString &fileName, const QString &newName)
{

}

QFile Username::FileForReadingMACAddress(const QString &fileName, const QString &newName)
{

}

bool Username::CheckingCorrectReadIpddress()
{

     return 1;
}

bool Username::CheckingCorrectReadMACddress()
{

     return 1;
}

bool Username::CheckingCorrectWriteIpddress()
{

     return 1;
}

bool Username::CheckingCorrectWriteMACddress()
{

    return 1;
}
*/
