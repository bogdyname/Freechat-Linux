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
       //File for check read && write MAC address

       QFile CheckUserMACAddress;
       QFile CheckWroteMACFile;
       QFile CheckReadedMACFile;
       QFile WriteUserMACAddressToUserIpAddress;

       //Files for check read && write IP address

       QFile CheckUserIpAddress;
       QFile CheckWroteIpFile;
       QFile CheckReadedIpFile;
       QFile CheckWriterFileMACToIp;

    Username(QObject *parent = nullptr);

signals:
    void AskUserForReadContactName();
    void AskUserForWriteContactName();
    void MessegBoxWithCheckingCorrectReadContactName();
    void MessegBoxWithCheckingCorrectWriteContactName();


private slots:
    void FileForWritingIpAddress(const QString &name);
    void FileForWritingMACAddress(const QString &name);

public slots:
    void FileForReadingIpAddress(const QString &fileName, const QString &newName);
    void FileForReadingMACAddress(const QString &fileName, const QString &newName);

protected slots:
    void CheckingCorrectReadIpddress();
    void CheckingCorrectReadMACddress();
    void CheckingCorrectWriteIpddress();
    void CheckingCorrectWriteMACddress();

};

#endif // USERNAME_H
