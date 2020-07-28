#include "customlistwidget.h"

CustomListWidget::CustomListWidget(QWidget *parent)
    : QListWidget(parent)
{
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setSelectionBehavior(QAbstractItemView::SelectItems);
    this->setDragDropMode(QAbstractItemView::DropOnly);
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    //Setting up ListWidgets
    //DRAG AND DROP MODEL
    this->setDragEnabled(true);
    this->setAcceptDrops(true);

    return;
}

void CustomListWidget::dropEvent(QDropEvent *event)
{
    qDebug() << "DATA TEST: " << event->mimeData()->text();

    /*
    //current indexes
   for(int iter = 0; iter < musicList->count(); ++iter)
   {
       QListWidgetItem *track = musicList->item(iter);
       currentIndexesOfTracks.push_back(track->text());
   }

   for(int iter = 0; iter < musicList->count(); ++iter)
    qDebug() << "Indexes: " << currentIndexesOfTracks.at(iter);
    */

    return;
}
