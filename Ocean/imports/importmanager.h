/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#ifndef IMPORTMANAGER_H
#define IMPORTMANAGER_H

#include <QDir>
#include <QFile>
#include <QFileDialog>

#include <QDebug>
#include <QCoreApplication>

class ImportManager : public QFile
{
    Q_OBJECT

public:
    ImportManager();
    ~ImportManager();

    //Connect it in UI code
    //Need to connect object of this class with slots of this class inside Ocean.cpp
public slots:
    void SaveFileIntoMusicFolder(const QString &pathOfmp3);
    void SaveFilesIntoMusicFolder(const QStringList &pathsOfmp3);

private:
    bool CheckDir();
    QString GetNameOfSongFromCurrentPath(const QString nameOfSong);

    //Objects of Qt
private:
    QDir *musicDir = nullptr;
    QFile *mp3File = nullptr;
    QFileDialog *importerWindow = nullptr;//TTS CODE LIKE EXAMPLE FOR Ocean.cpp
};

#endif
