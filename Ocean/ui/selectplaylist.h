/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#ifndef SELECTPLAYLIST_H
#define SELECTPLAYLIST_H

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QDebug>

#include "ui_selectplaylist.h"

class SelectPlaylist : public QWidget, private Ui::SelectedPlaylist
{
    Q_OBJECT
    Q_CLASSINFO("Version", "1.0")

public:
    SelectPlaylist(QWidget *parent = nullptr);
    ~SelectPlaylist();

signals:
    void CallOutToPassStringFromWidget(const QString &name);
    void BreakeWidget();

public:
    void PassAllPlaylistsIntoWidget(const QStringList &list);
    const QString GetNameOfSelectedPlaylist();

private slots:
    void SelectNameOfPlayList(QListWidgetItem *item);
    void ClickedCancel();

    //Objects
private:
    QString selectedName;
    QPushButton *cancel = nullptr;
    QListWidget *playlists = nullptr;

private:
    Ui::SelectedPlaylist *ui;
};

#endif
