/*
***Copyright (C) 2019 Softwater Inc
***Contact: bogdyname@gmail.com
*/

#ifndef USERNAME_H
#define USERNAME_H

#include <QTextStream>
#include <QDataStream>
#include <QSettings>
#include <QFile>

class Username : public QFile
{
    Q_OBJECT

public:
    Username(QObject *parent = nullptr);

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

signals:
    bool AskUserForReadContactName();
    bool AskUserForWriteContactName();

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
