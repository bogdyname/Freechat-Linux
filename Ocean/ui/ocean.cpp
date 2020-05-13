/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#include "ui/ocean.h"

Ocean::Ocean(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Ocean)
{
    Ocean::ui->setupUi(this);

    //ALLOCATE MEMORY
    try
    {
        //Objects of UI
        Ocean::imageOfPlayList = new QLabel();
        Ocean::sortBy = new QComboBox();
        Ocean::sliderOfTrack = new QSlider(Qt::Horizontal);
        Ocean::sliderOfVolume = new QSlider(Qt::Horizontal);
        Ocean::playLists = new QListWidget();
        Ocean::musicList = new QListWidget();
        Ocean::playTrack = new QPushButton();
        Ocean::stopTrack = new QPushButton();
        Ocean::nextTrack = new QPushButton();
        Ocean::previousTrack = new QPushButton();
        Ocean::buttonForAddMusicWithDel = new QPushButton();
        Ocean::buttonForAddMusicOnlyCopy = new QPushButton();

        //Object of own classes
        Ocean::createPlayList = new CreatePlayListWidget();
        Ocean::importManager = new ImportManager();
        Ocean::playlistmanager = new Playlist();
        Ocean::playermanager = new Player();
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

    /*--------------------------------------------------UI--------------------------------------------------*/
    //UpSide
    //Player
    Ocean::ui->buttonsOfPlayer->QHBoxLayout::addWidget(Ocean::stopTrack);
    Ocean::ui->buttonsOfPlayer->QHBoxLayout::addWidget(Ocean::previousTrack);
    Ocean::ui->buttonsOfPlayer->QHBoxLayout::addWidget(Ocean::playTrack);
    Ocean::ui->buttonsOfPlayer->QHBoxLayout::addWidget(Ocean::nextTrack);
    Ocean::ui->sliderOfPlayer->QHBoxLayout::addWidget(Ocean::sliderOfTrack);

    //Left side
    //Music
    Ocean::ui->music->QHBoxLayout::addWidget(Ocean::playLists);
    Ocean::ui->music->QHBoxLayout::addWidget(Ocean::musicList);

    //Right side
    //Image of play list
    Ocean::ui->tool->QVBoxLayout::addWidget(Ocean::imageOfPlayList);
    //slider for volume
    Ocean::ui->tool->QVBoxLayout::addWidget(Ocean::sliderOfVolume);
    //Tool buttons
    Ocean::ui->tool->QVBoxLayout::addWidget(Ocean::buttonForAddMusicWithDel);
    Ocean::ui->tool->QVBoxLayout::addWidget(Ocean::buttonForAddMusicOnlyCopy);
    Ocean::ui->tool->QVBoxLayout::addWidget(Ocean::sortBy);

    //Main window
    this->QWidget::setMinimumSize(250, 300);

    //Lists
    Ocean::playLists->QWidget::setMaximumWidth(225);
    Ocean::musicList->QWidget::setMaximumWidth(1500);
    Ocean::playLists->QAbstractItemView::setSelectionMode(QAbstractItemView::SingleSelection);
    Ocean::musicList->QAbstractItemView::setSelectionMode(QAbstractItemView::SingleSelection);
    Ocean::playLists->QAbstractItemView::setSelectionBehavior(QAbstractItemView::SelectRows);
    Ocean::musicList->QAbstractItemView::setSelectionBehavior(QAbstractItemView::SelectRows);
    Ocean::playLists->QWidget::setContextMenuPolicy(Qt::CustomContextMenu);
    Ocean::musicList->QWidget::setContextMenuPolicy(Qt::CustomContextMenu);

    Ocean::playLists->QListWidget::addItem("all");
    Ocean::playLists->QListWidget::addItem("TTS");

    //Slider of volume
    Ocean::sliderOfVolume->QWidget::setMinimumSize(225, 17);
    Ocean::sliderOfVolume->QWidget::setMaximumSize(225, 17);

    //Sort box
    Ocean::sortBy->QComboBox::addItem("Default");
    Ocean::sortBy->QComboBox::addItem("Name");
    Ocean::sortBy->QComboBox::addItem("Date");
    Ocean::sortBy->QComboBox::addItem("Group");
    Ocean::sortBy->QWidget::setMinimumSize(225, 17);
    Ocean::sortBy->QWidget::setMaximumSize(225, 17);

    //Buttons for open file
    Ocean::buttonForAddMusicWithDel->QPushButton::setText("Add music with delete");
    Ocean::buttonForAddMusicOnlyCopy->QPushButton::setText("Add music with copy");
    Ocean::buttonForAddMusicWithDel->QWidget::setMinimumSize(225, 17);
    Ocean::buttonForAddMusicOnlyCopy->QWidget::setMinimumSize(225, 17);
    Ocean::buttonForAddMusicWithDel->QWidget::setMaximumSize(225, 17);
    Ocean::buttonForAddMusicOnlyCopy->QWidget::setMaximumSize(225, 17);

    //Buttons for player
    Ocean::stopTrack->QPushButton::setText("Stop");
    Ocean::previousTrack->QPushButton::setText("Previous");
    Ocean::playTrack->QPushButton::setText("Play");
    Ocean::nextTrack->QPushButton::setText("Next");
    /*--------------------------------------------------UI--------------------------------------------------*/

    /*--------------------------------------------------MANAGERS--------------------------------------------------*/


    /*--------------------------------------------------MANAGERS--------------------------------------------------*/

    /*
        *!CONNECT SIGNALS WITH SLOTS!*
    Import manager connect
        1.1) Add new music and delete it via button
        1.2) Add new music (only copy) via button
    Player manager
        2.1) play track
        2.2) stop track
        2.3) set current playlist via playlist manager (emited signal from SLOT(SetPlayList(QListWidgetItem *)))
    Playlist manager
        3.1) next track
        3.2) previous track
    UI lists widgets
        4.1) set playlist then item clicked (UI only)
        4.2) Context Menu for playlist
        4.3) Context Menu for music list
    */
    //Import manager
    QObject::connect(Ocean::buttonForAddMusicWithDel, SIGNAL(clicked(bool)), Ocean::importManager, SLOT(CallFileDialogWithDel()));
    QObject::connect(Ocean::buttonForAddMusicOnlyCopy, SIGNAL(clicked(bool)), Ocean::importManager, SLOT(CallFileDialogOnlyCopy()));
    //Player manager
    QObject::connect(Ocean::playTrack, &QPushButton::clicked, Ocean::playermanager, &QMediaPlayer::play);
    QObject::connect(Ocean::stopTrack, &QPushButton::clicked, Ocean::playermanager, &QMediaPlayer::stop);
    QObject::connect(Ocean::playlistmanager, &Playlist::SetPlayCurrentList, Ocean::playermanager, &QMediaPlayer::setPlaylist);
    //Playlist manager
    QObject::connect(Ocean::nextTrack, &QPushButton::clicked, Ocean::playlistmanager, &QMediaPlaylist::next);
    QObject::connect(Ocean::previousTrack, &QPushButton::clicked, Ocean::playlistmanager, &QMediaPlaylist::previous);
    //UI Lists
    QObject::connect(Ocean::playLists, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(SetPlayList(QListWidgetItem *)));
    QObject::connect(Ocean::playLists, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(ShowContextMenuOfPlayList(QPoint)));
    QObject::connect(Ocean::musicList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(ShowContextMenuOfMusicList(QPoint)));

    QObject::connect(Ocean::createPlayList, &CreatePlayListWidget::BreakeWidget, this, &Ocean::CloseWidgetViaCancel);
    QObject::connect(Ocean::createPlayList, &CreatePlayListWidget::SendNameOfPlayList, this, &Ocean::CloseWidgetViaOkay);

    return;
}

Ocean::~Ocean()
{
    //UI
    delete Ocean::ui;
    delete Ocean::imageOfPlayList;
    delete Ocean::sortBy;
    delete Ocean::sliderOfTrack;
    delete Ocean::sliderOfVolume;
    delete Ocean::playLists;
    delete Ocean::musicList;
    delete Ocean::playTrack;
    delete Ocean::stopTrack;
    delete Ocean::nextTrack;
    delete Ocean::previousTrack;
    delete Ocean::buttonForAddMusicWithDel;
    delete Ocean::buttonForAddMusicOnlyCopy;

    //Own classes
    delete Ocean::importManager;
    delete Ocean::playlistmanager;
    delete Ocean::playermanager;
    delete Ocean::createPlayList;

    return;
}
// NOT DONE
void Ocean::Hidder()
{
    Ocean::playLists->QWidget::hide();
    Ocean::musicList->QWidget::hide();
    Ocean::sortBy->QWidget::hide();
    Ocean::buttonForAddMusicWithDel->QWidget::hide();
    Ocean::buttonForAddMusicOnlyCopy->QWidget::hide();

    return;
}
// NOT DONE
void Ocean::Shower()
{
    Ocean::playLists->QWidget::show();
    Ocean::musicList->QWidget::show();
    Ocean::sortBy->QWidget::show();
    Ocean::buttonForAddMusicWithDel->QWidget::show();
    Ocean::buttonForAddMusicOnlyCopy->QWidget::show();

    return;
}
// NOT DONE
void Ocean::ShowContextMenuOfPlayList(const QPoint &point)
{
    QPoint globalPoint = Ocean::playLists->QWidget::mapToGlobal(point);

    // Create menu and insert some actions
    QMenu myMenu;
    myMenu.QMenu::addAction("Create", this, SLOT(CreatePlaylist()));
    myMenu.QMenu::addAction("Delete", this, SLOT(EraseItemFromPlayList()));

    // Show context menu at handling position
    myMenu.QMenu::exec(globalPoint);

    //write here method from playlist.h

    return;
}
// NOT DONE
void Ocean::ShowContextMenuOfMusicList(const QPoint &point)
{
    QPoint globalPoint = Ocean::playLists->QWidget::mapToGlobal(point);

    QMenu myMenu;
    myMenu.QMenu::addAction("Delete", this, SLOT(EraseItemFromMusicList()));

    myMenu.QMenu::exec(globalPoint);

    //write here method from importmanager.h

    return;
}

void Ocean::EraseItemFromMusicList()
{
    // If multiple selection is on, we need to erase all selected items
    for (unsigned short int iter = 0; iter < Ocean::musicList->QListWidget::selectedItems().QList::size(); ++iter)
    {
        // Get curent item on selected row
        QListWidgetItem *item = Ocean::musicList->QListWidget::takeItem(Ocean::musicList->QListWidget::currentRow());
        // And remove it
        delete item;
    }

    return;
}

void Ocean::EraseItemFromPlayList()
{
    for (unsigned short int iter = 0; iter < Ocean::playLists->QListWidget::selectedItems().QList::size(); ++iter)
    {
        QListWidgetItem *item = Ocean::playLists->QListWidget::takeItem(Ocean::playLists->QListWidget::currentRow());

        delete item;
    }

    return;
}

void Ocean::CreatePlaylist()
{
    this->QWidget::setDisabled(true);
    Ocean::createPlayList->QWidget::show();

    return;
}

void Ocean::SetPlayList(QListWidgetItem *item)
{
    if(item->QListWidgetItem::text() == "all")
        Ocean::playlistmanager->Playlist::LoadDefaultPlayList();
    else
        Ocean::playlistmanager->Playlist::LoadPlayList(item->QListWidgetItem::text());

    //Emit signal from Playlist.h with current playlist
    emit Ocean::playlistmanager->Playlist::SetPlayCurrentList(Ocean::playlistmanager->Playlist::GetPlayList());

    return;
}

void Ocean::CloseWidgetViaCancel()
{
    this->QWidget::setEnabled(true);
    Ocean::createPlayList->QWidget::hide();

    return;
}

void Ocean::CloseWidgetViaOkay(const QString &name)
{
    //before delete widget need to pass data into playlist

    this->QWidget::setEnabled(true);
    Ocean::createPlayList->QWidget::hide();

    return;
}

void Ocean::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    int short h = event->QResizeEvent::size().QSize::height();
    int short w = event->QResizeEvent::size().QSize::width();

    if(h <= 500 && w <= 500)
        Ocean::Hidder();
    else
        Ocean::Shower();

    return;
}
