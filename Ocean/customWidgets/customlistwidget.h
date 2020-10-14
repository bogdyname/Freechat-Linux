/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#ifndef CUSTOMLISTWIDGET_H
#define CUSTOMLISTWIDGET_H

#include <QDrag>
#include <QDebug>
#include <QObject>
#include <QBuffer>
#include <QMimeData>
#include <QListWidget>
#include <QDragMoveEvent>

class CustomListWidget : public QListWidget
{
    Q_OBJECT

public:
    CustomListWidget(QWidget *parent = nullptr);

signals:
    void CallOutItemsDroped(const QStringList &files);

protected:
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dragMoveEvent(QDragMoveEvent *event);
    virtual void dropEvent(QDropEvent* event);
};

#endif
