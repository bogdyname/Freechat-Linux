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
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->hide();

    try
    {
        //Objects of UI
        addedSongs = new QListWidget(this);
        allSongs = new QListWidget(this);
        okay = new QPushButton("okay", this);
        cancel = new QPushButton("cancel", this);
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
    ui->verticalLayout->addWidget(cancel);
    ui->horizontalLayout->addWidget(addedSongs);
    ui->horizontalLayout->addWidget(allSongs);
    ui->verticalLayout_2->addWidget(okay);

    //SIGNALS/SLOTS
    //Button
    connect(cancel, &QPushButton::clicked, this, &AddMusicWidget::ClickedCancel);
    connect(okay, &QPushButton::clicked, this, &AddMusicWidget::ClickedOkay);
    //Lists
    connect(addedSongs, &QListWidget::itemDoubleClicked, this, &AddMusicWidget::DoubleClickedAddedSongsList);
    connect(allSongs, &QListWidget::itemDoubleClicked, this, &AddMusicWidget::DoubleClickedAllSongsList);

    return;
}

AddMusicWidget::~AddMusicWidget()
{
    delete ui;

    qDebug() << "Destructor from AddMusicWidget.cpp";
}

void AddMusicWidget::DoubleClickedAllSongsList(QListWidgetItem *item)
{
    addedSongs->addItem(item->text());

    return;
}

void AddMusicWidget::DoubleClickedAddedSongsList(QListWidgetItem *item)
{
    for (unsigned short int iter = 0; iter < addedSongs->selectedItems().size(); ++iter)
    {
        item = addedSongs->takeItem(addedSongs->currentRow());

        delete item;
    }

    return;
}

void AddMusicWidget::ClickedCancel()
{
    allSongs->clear();
    addedSongs->clear();
    emit this->BreakeWidget();

    return;
}

void AddMusicWidget::ClickedOkay()
{
    emit this->SendListWithSongs(GetAddedSongsFromListWidget());

    allSongs->clear();
    addedSongs->clear();

    return;
}

QStringList AddMusicWidget::GetAddedSongsFromListWidget()
{
    listWithAddedSongs.clear();

    for(unsigned short int iter = 0; iter < addedSongs->count(); ++iter)
    {
        QListWidgetItem* item = addedSongs->item(iter);
        listWithAddedSongs.push_back(item->text());
    }

    return listWithAddedSongs;
}

void AddMusicWidget::GetAllSongsfFromMainWindow(const QStringList &list)
{
    allSongs->addItems(list);

    return;
}
