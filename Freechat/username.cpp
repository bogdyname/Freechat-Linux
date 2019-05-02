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
            this, SLOT(FileForWritingIpAddress()));
    connect(   , SIGNAL(AskUserForReadContactName()),
            this, SLOT(FileForWritingMACAddress()));
    connect(   , SIGNAL(AskUserForWriteContactName()),
            this, SLOT(FileForReadingIpAddress();));
    connect(   , SIGNAL(AskUserForWriteContactName()),
            this, SLOT(FileForReadingMACAddress();));

    userMACAddress.setFileName("userMAC.txt");
    writeUserMACAddressToUserIpAddress.setFileName("swapmtoi.txt");
    userIpAddress.setFileName("userIP.txt");
    checkWriterFileMACToIp.setFileName("swapmtoipo.txt");
}

bool Username::CheckingForExistsIpddress()
{

}

bool Username::CheckingForExistsMACddress()
{

}

bool Username::CheckForIpFileIsOpen()
{

}

bool Username::CheckForMACFileIsOpen()
{

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

void Username::FileForWritingIpAddress()
{

}

void Username::FileForWritingMACAddress()
{

}

void Username::FileForReadingIpAddress()
{

}

void Username::FileForReadingMACAddress()
{

}
