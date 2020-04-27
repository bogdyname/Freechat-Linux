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

class ImportManager : public QFile
{
    Q_OBJECT

public:
    ImportManager();
    ~ImportManager();

public slots:
    //SavingFiles
    //for file dialog (looking for file in finder)
    void SaveFileIntoMusicFolder(const QString &pathOfmp3);

private:

    //Objects of Qt
private:
    QFile *mp3 = nullptr;
    QFileDialog *importerWindow = nullptr;
};

#endif
