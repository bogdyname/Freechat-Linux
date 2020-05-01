/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#ifndef OCEAN_H
#define OCEAN_H

#include <QDebug>
#include <QWidget>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QMainWindow>
#include <QStringList>
#include <QTextBrowser>
#include <QMessageBox>
#include "ui_ocean.h"

#include "imports/importmanager.h"

class Ocean : public QMainWindow, private Ui::Ocean
{
    Q_OBJECT

public:
    Ocean(QWidget *parent = nullptr);
    ~Ocean();

private:
    QListWidget *listMusic;
    QPushButton *buttonForAddMusicWithDel;
    QPushButton *buttonForAddMusicOnlyCopy;

    //Own Objects
private:
    ImportManager *importManager = nullptr;

private:
    Ui::Ocean *ui;
};
#endif
