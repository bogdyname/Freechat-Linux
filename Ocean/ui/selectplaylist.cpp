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
        cancel = new QPushButton("cancel");
        playlists = new QListWidget();
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

    selectedName  = "";

    //setting up UI
    ui->verticalLayout->addWidget(cancel);
    ui->verticalLayout->addWidget(playlists);

    //SIGNAL/SLOTS
    QObject::connect(playlists, &QListWidget::itemDoubleClicked, this, &SelectPlaylist::SelectNameOfPlayList);
    QObject::connect(cancel, &QPushButton::clicked, this, &SelectPlaylist::ClickedCancel);
}

SelectPlaylist::~SelectPlaylist()
{
    qDebug() << "Destructor from SelectPlaylist.cpp";

    delete ui;
    delete cancel;
    delete playlists;
}

void SelectPlaylist::PassAllPlaylistsIntoWidget(const QStringList &list)
{
    playlists->clear();
    playlists->addItems(list);

    return;
}

const QString SelectPlaylist::GetNameOfSelectedPlaylist()
{
    return selectedName;
}

void SelectPlaylist::SelectNameOfPlayList(QListWidgetItem *item)
{
    selectedName.clear();
    selectedName = item->text();
    emit this->CallOutToPassStringFromWidget(selectedName);
    this->hide();

    return;
}

void SelectPlaylist::ClickedCancel()
{
    emit this->BreakeWidget();

    return;
}
