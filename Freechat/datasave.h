/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef DATASAVE_H
#define DATASAVE_H

#include <QTextStream>
#include <QSaveFile>
#include <QIODevice>
#include <QWidget>
#include <QFile>

class Freechat;
class Username;

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
    void CheckUsernameForSaveFile();

public slots:
    void AbortProgWheneverMemorySizeFull();
    void SaveFileForUsername();
};

#endif // DATASAVE_H
