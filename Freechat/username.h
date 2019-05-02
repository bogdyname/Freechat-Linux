/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef USERNAME_H
#define USERNAME_H

#include <QTextStream>
#include <QDataStream>
#include <QString>
#include <QFile>
#include <QList>

class Freechat;
class UserClient;
class Connection;
class Usernametable;

class Username : public QFile
{
    Q_OBJECT

public:
    QFile userMACAddress;
    QFile writeUserMACAddressToUserIpAddress;
    QFile userIpAddress;
    QFile checkWriterFileMACToIp;

    Username(QObject *parent = nullptr);

signals:
    void AskUserForReadContactName();
    void AskUserForWriteContactName();

private slots:
    void FileForWritingIpAddress();
    void FileForWritingMACAddress();

public slots:
    void FileForReadingIpAddress();
    void FileForReadingMACAddress();

protected:
    bool CheckingForExistsIpddress();
    bool CheckingForExistsMACddress();
    bool CheckForIpFileIsOpen();
    bool CheckForMACFileIsOpen();

};

#endif // USERNAME_H
