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

void Username::ReadingIpAddress()
{

}

void Username::ReadingMACAddress()
{

}
