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
    connect(   , SIGNAL(AskUserForReadContactName()),
            this, SLOT(FileForWritingIpAddress(const QString &name)));
    connect(   , SIGNAL(AskUserForReadContactName()),
            this, SLOT(FileForWritingMACAddress(const QString &name)));
    connect(   , SIGNAL(AskUserForWriteContactName()),
            this, SLOT(FileForReadingIpAddress(const QString &fileName, const QString &newName);));
    connect(   , SIGNAL(AskUserForWriteContactName()),
            this, SLOT(FileForReadingMACAddress(const QString &fileName, const QString &newName);));

    connect(   , SIGNAL(MessegBoxWithCheckingCorrectReadContactName()),
            this, SLOT(CheckingCorrectReadIpddress()));
    connect(   , SIGNAL(MessegBoxWithCheckingCorrectReadContactName()),
            this, SLOT(CheckingCorrectReadMACddress()));
    connect(   , SIGNAL(MessegBoxWithCheckingCorrectWriteContactName),
            this, SLOT(CheckingCorrectWriteIpddress()));
    connect(   , SIGNAL(MessegBoxWithCheckingCorrectWriteContactName),
            this, SLOT(CheckingCorrectWriteMACddress()));
}



void Username::AskUserForReadContactName()
{
    QMessageBox::ask(this, tr("Read contact"),
    tr("Do you want to read this contact?"));
}

void Username::AskUserForWriteContactName()
{
    QMessageBox::ask(this, tr("Write contact"),
    tr("Do you want to write this contact?"));
}

void Username::MessegBoxWithCheckingCorrectReadContactName()
{


}

void Username::MessegBoxWithCheckingCorrectWriteContactName()
{


}

void Username::FileForWritingIpAddress(const QString &name)
{

}

void Username::CheckingCorrectWriteIpddress()
{


}

void Username::FileForWritingMACAddress(const QString &name)
{

}

void Username::CheckingCorrectWriteMACddress()
{


}

void Username::FileForReadingIpAddress(const QString &fileName, const QString &newName)
{

}

void Username::CheckingCorrectReadIpddress()
{


}

void Username::FileForReadingMACAddress(const QString &fileName, const QString &newName)
{

}

void Username::CheckingCorrectReadMACddress()
{


}
