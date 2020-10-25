/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#include "customlistwidget.h"

CustomListWidget::CustomListWidget(QWidget *parent)
    : QListWidget(parent)
{
    //Setting up ListWidgets
    //DRAG AND DROP MODEL
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setSelectionBehavior(QAbstractItemView::SelectItems);
    this->setDragDropMode(QAbstractItemView::InternalMove);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setDefaultDropAction(Qt::MoveAction);
    this->setDropIndicatorShown(true);
    this->setDragEnabled(true);
    this->setAcceptDrops(true);

    return;
}

void CustomListWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();

    return;
}

void CustomListWidget::dragMoveEvent(QDragMoveEvent *event)
{
    event->accept();

    return;
}

void CustomListWidget::dropEvent(QDropEvent* event)
{
    QList<QUrl> urlList = event->mimeData()->urls();
    QStringList buffer = {};

    foreach(QUrl url, urlList)
        buffer.push_back(url.toString());

    emit this->CallOutItemsDroped(buffer);

    return;
}
