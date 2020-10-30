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
    //
    if(event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();

    return;
}

void CustomListWidget::dragMoveEvent(QDragMoveEvent *event)
{
    //can accept drop items
    event->accept();

    return;
}

void CustomListWidget::dropEvent(QDropEvent* event)
{
    //list for path of files
    QList<QUrl> urlList = event->mimeData()->urls();
    //list only for audio files
    QStringList buffer = {};

    //parsing all paths of files to get only audio files
    foreach(QUrl url, urlList)
        buffer.push_back(url.toString());

    //pass paths of audio files into import manager
    emit this->CallOutItemsDroped(buffer);

    return;
}
