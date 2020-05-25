/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#include "selectplaylist.h"

SelectPlaylist::SelectPlaylist(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SelectedPlaylist)
{
    SelectPlaylist::ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    try
    {
        //Objects of UI
        SelectPlaylist::cancel = new QPushButton("cancel");
        SelectPlaylist::playlists = new QListWidget();
    }
    catch(std::bad_alloc &exp)
    {
        #ifndef Q_DEBUG
        qCritical() << "Exception caught: " << exp.std::bad_alloc::what();
        #endif
        abort();
    }
    catch(...)
    {
        #ifndef Q_DEBUG
        qCritical() << "Some exception caught";
        #endif
        abort();
    }

    SelectPlaylist::selectedName  = "";

    //setting up UI
    SelectPlaylist::ui->verticalLayout->QHBoxLayout::addWidget(SelectPlaylist::cancel);
    SelectPlaylist::ui->verticalLayout->QHBoxLayout::addWidget(SelectPlaylist::playlists);

    //SIGNAL/SLOTS
    QObject::connect(SelectPlaylist::playlists, &QListWidget::itemDoubleClicked, this, &SelectPlaylist::SelectNameOfPlayList);
    QObject::connect(SelectPlaylist::cancel, &QPushButton::clicked, this, &SelectPlaylist::ClickedCancel);
}

SelectPlaylist::~SelectPlaylist()
{
    delete SelectPlaylist::ui;
    delete SelectPlaylist::cancel;
    delete SelectPlaylist::playlists;
}

void SelectPlaylist::PassAllPlaylistsIntoWidget(const QStringList &list)
{
    SelectPlaylist::playlists->QListWidget::addItems(list);

    return;
}

QString SelectPlaylist::GetNameOfSelectedPlaylist()
{
    return SelectPlaylist::selectedName;
}

void SelectPlaylist::SelectNameOfPlayList(QListWidgetItem *item)
{
    SelectPlaylist::selectedName = item->QListWidgetItem::text();
    emit this->CallOutToPassStringFromWidget(SelectPlaylist::selectedName);

    return;
}

void SelectPlaylist::ClickedCancel()
{
    emit this->SelectPlaylist::BreakeWidget();

    return;
}
