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
}
