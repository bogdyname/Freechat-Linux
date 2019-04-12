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

class UserClient;
class Usernametable;

class Username : public QFile
{
    Q_OBJECT

public:
    enum VariblesForMACAddress
    {
        CheckUserMACAddress,
        CheckWroteMACFile,
        CheckReadedMACFile,
        WriteUserMACAddressToUserIpAddress
    };


    enum VariblesForIpAddress
    {
        CheckUserIpAddress,
        CheckWroteIpFile,
        CheckReadedIpFile,
        CheckWriterFileMACToIp
    };

    Username(QObject *parent = nullptr);

signals:
    bool AskUserForReadContactName();
    bool AskUserForWriteContactName();
    bool MessegBoxWithCheckingCorrectReadContactName();
    bool MessegBoxWithCheckingCorrectWriteContactName();

public slots:
    QFile FileForWritingIpAddress(const QString &name);
    QFile FileForWritingMACAddress(const QString &name);
    QFile FileForReadingIpAddress(const QString &fileName, const QString &newName);
    QFile FileForReadingMACAddress(const QString &fileName, const QString &newName);

private slots:
    bool CheckingCorrectReadIpddress();
    bool CheckingCorrectReadMACddress();
    bool CheckingCorrectWriteIpddress();
    bool CheckingCorrectWriteMACddress();
};

#endif // USERNAME_H
