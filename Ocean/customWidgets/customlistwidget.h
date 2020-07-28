#ifndef CUSTOMLISTWIDGET_H
#define CUSTOMLISTWIDGET_H

#include <QDebug>
#include <QObject>
#include <QMimeData>
#include <QListWidget>
#include <QDragMoveEvent>

class CustomListWidget : public QListWidget
{
    Q_OBJECT

public:
    CustomListWidget(QWidget *parent = nullptr);

private:
    virtual void dropEvent(QDropEvent *event);
};

#endif
