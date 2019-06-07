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

class Freechat;
class Connection;
class Usernametable;

class Username : public QFile
{
    Q_OBJECT

public:
    Username(QObject *parent = nullptr);

public slots:
    void ReadingIpAddress();
    void ReadingMACAddress();
};

#endif // USERNAME_H
