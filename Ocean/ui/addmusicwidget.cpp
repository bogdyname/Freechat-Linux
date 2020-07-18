/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#include "addmusicwidget.h"

AddMusicWidget::AddMusicWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddMusicWidget)
{
    AddMusicWidget::ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    try
    {
        //Objects of UI
        AddMusicWidget::addedSongs = new QListWidget(this);
        AddMusicWidget::allSongs = new QListWidget(this);
        AddMusicWidget::okay = new QPushButton("okay", this);
        AddMusicWidget::cancel = new QPushButton("cancel", this);
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

    //Ui settings
    AddMusicWidget::ui->verticalLayout->QVBoxLayout::addWidget(AddMusicWidget::cancel);
    AddMusicWidget::ui->horizontalLayout->QHBoxLayout::addWidget(AddMusicWidget::addedSongs);
    AddMusicWidget::ui->horizontalLayout->QHBoxLayout::addWidget(AddMusicWidget::allSongs);
    AddMusicWidget::ui->verticalLayout_2->QVBoxLayout::addWidget(AddMusicWidget::okay);

    //SIGNALS/SLOTS
    //Button
    QObject::connect(AddMusicWidget::cancel, &QPushButton::clicked, this, &AddMusicWidget::ClickedCancel);
    QObject::connect(AddMusicWidget::okay, &QPushButton::clicked, this, &AddMusicWidget::ClickedOkay);
    //Lists
    QObject::connect(AddMusicWidget::addedSongs, &QListWidget::itemDoubleClicked, this, &AddMusicWidget::DoubleClickedAddedSongsList);
    QObject::connect(AddMusicWidget::allSongs, &QListWidget::itemDoubleClicked, this, &AddMusicWidget::DoubleClickedAllSongsList);

    return;
}

AddMusicWidget::~AddMusicWidget()
{
    delete AddMusicWidget::ui;

    qDebug() << "Destructor from AddMusicWidget.cpp";
}

void AddMusicWidget::DoubleClickedAllSongsList(QListWidgetItem *item)
{
    AddMusicWidget::addedSongs->QListWidget::addItem(item->QListWidgetItem::text());

    return;
}

void AddMusicWidget::DoubleClickedAddedSongsList(QListWidgetItem *item)
{
    for (unsigned short int iter = 0; iter < AddMusicWidget::addedSongs->QListWidget::selectedItems().QList::size(); ++iter)
    {
        item = AddMusicWidget::addedSongs->QListWidget::takeItem(AddMusicWidget::addedSongs->QListWidget::currentRow());

        delete item;
    }

    return;
}

void AddMusicWidget::ClickedCancel()
{
    AddMusicWidget::allSongs->QListWidget::clear();
    AddMusicWidget::addedSongs->QListWidget::clear();
    emit this->AddMusicWidget::BreakeWidget();

    return;
}

void AddMusicWidget::ClickedOkay()
{
    emit this->AddMusicWidget::SendListWithSongs(AddMusicWidget::GetAddedSongsFromListWidget());

    AddMusicWidget::allSongs->QListWidget::clear();
    AddMusicWidget::addedSongs->QListWidget::clear();

    return;
}

QStringList AddMusicWidget::GetAddedSongsFromListWidget()
{
    for(unsigned short int iter = 0; iter < AddMusicWidget::addedSongs->QListWidget::count(); ++iter)
    {
        QListWidgetItem* item = AddMusicWidget::addedSongs->item(iter);
        AddMusicWidget::listWithAddedSongs.QStringList::push_back(item->text());
    }

    return AddMusicWidget::listWithAddedSongs;
}

void AddMusicWidget::GetAllSongsfFromMainWindow(const QStringList &list)
{
    AddMusicWidget::allSongs->QListWidget::addItems(list);

    return;
}
