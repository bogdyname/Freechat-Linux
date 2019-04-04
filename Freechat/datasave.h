/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef DATASAVE_H
#define DATASAVE_H

#include <QTextStream>
#include <QSaveFile>
#include <QIODevice>
#include <QFile>

class Freechat;
class Duinterface;

class Datasave : public QSaveFile
{
    Q_OBJECT

public:
    bool saveFileVariable = false;
    bool deleteFileVariable = false;

public:
    Datasave(QObject *parent = nullptr);

    bool SaveFile();
    bool DeleteFile();
    QFile DataWriterInFile(QFile &fileWithData);

signals:
    void CheckYourMemorySize();
    void AborProgWheneverMemorySizeFull();
};

#endif // DATASAVE_H
