/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#ifndef ADDMUSICWIDGET_H
#define ADDMUSICWIDGET_H

#include <QDebug>
#include <QWidget>
#include <QListWidget>
#include <QPushButton>

#include "ui_addmusicwidget.h"

class AddMusicWidget : public QWidget, private Ui::AddMusicWidget
{
    Q_OBJECT
    Q_CLASSINFO("Version", "1.0")

public:
    explicit AddMusicWidget(QWidget *parent = nullptr);
    ~AddMusicWidget();

signals:
    void SendListWithSongs(const QStringList &songs);
    void BreakeWidget();

private slots:
    void DoubleClickedAllSongsList(QListWidgetItem *item);
    void DoubleClickedAddedSongsList(QListWidgetItem *item);

    void ClickedCancel();
    void ClickedOkay();

public:
    void GetAllSongsfFromMainWindow(const QStringList &list);

private:
    QStringList GetAddedSongsFromListWidget();

private:
    QListWidget *addedSongs = nullptr;
    QListWidget *allSongs = nullptr;
    QPushButton *cancel = nullptr;
    QPushButton *okay = nullptr;

private:
    QStringList listWithAddedSongs  = {};

private:
    Ui::AddMusicWidget *ui;
};

#endif
