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
        Ocean::spacer = new QSpacerItem(200, 0);
        Ocean::ownImage = new QPixmap();
        Ocean::imageOfPlayList = new QLabel();
        Ocean::nameOfTrack = new QLabel("'name of track'");
        Ocean::sortBy = new QComboBox();
        Ocean::sliderOfTrack = new QSlider(Qt::Horizontal);
        Ocean::sliderOfVolume = new QSlider(Qt::Horizontal);
        Ocean::playLists = new QListWidget();
        Ocean::musicList = new QListWidget();
        Ocean::playTrack = new QPushButton();
        Ocean::pauseTrack = new QPushButton();
        Ocean::stopTrack = new QPushButton();
        Ocean::nextTrack = new QPushButton();
        Ocean::previousTrack = new QPushButton();
     //   Ocean::buttonForAddMusicWithDel = new QPushButton();
     //   Ocean::buttonForAddMusicOnlyCopy = new QPushButton();

        //Tools for widgets
        Ocean::timerForCheckWidgets = new QTimer();
        Ocean::timerForCheckDefaultPlayList = new QTimer();
        Ocean::cd = new QDir();

        //Object of own classes
        //widgets
        Ocean::getAddedTracksFromWidget = new AddMusicWidget();
        Ocean::getStringFromUser = new GetStringWidget();
        Ocean::getStringWithSelectedPlaylist = new SelectPlaylist();
        //managers
        Ocean::importManager = new ImportManager();
        Ocean::playlistmanager = new Playlist();
        Ocean::playermanager = new Player();
        //system
        sysmanager = new System();
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
    Ocean::ui->setMode->QVBoxLayout::addWidget(Ocean::sortBy);
    Ocean::ui->playSlider->QVBoxLayout::addWidget(Ocean::nameOfTrack);
    Ocean::nameOfTrack->QObject::setObjectName("nameOfTrack");
    Ocean::ui->playSlider->QVBoxLayout::addWidget(Ocean::sliderOfTrack);
    Ocean::ui->playSlider->QLayout::setAlignment(Ocean::nameOfTrack, Qt::AlignJustify);

    //Left side
    //Music
    Ocean::ui->music->QHBoxLayout::addWidget(Ocean::playLists);
    Ocean::ui->music->QHBoxLayout::addWidget(Ocean::musicList);

    //Right side
    //Image of play list
    Ocean::ui->image->QVBoxLayout::addWidget(Ocean::imageOfPlayList);
    Ocean::ui->volumeSlider->QVBoxLayout::addWidget(Ocean::sliderOfVolume);
    Ocean::ui->buttonsOfTracks->QHBoxLayout::addWidget(Ocean::previousTrack);
    Ocean::ui->buttonsOfTracks->QHBoxLayout::addWidget(Ocean::nextTrack);
    Ocean::ui->buttonsOfTracks->QHBoxLayout::addWidget(Ocean::pauseTrack);
    Ocean::ui->buttonsOfTracks->QHBoxLayout::addWidget(Ocean::playTrack);
    Ocean::ui->tool->QLayout::setAlignment(Qt::AlignTop);
    //slider for volume

    //Tool buttons
 //   Ocean::ui->tool->QVBoxLayout::addWidget(Ocean::buttonForAddMusicWithDel);
 //   Ocean::ui->tool->QVBoxLayout::addWidget(Ocean::buttonForAddMusicOnlyCopy);

    //Main window  
    this->QWidget::setMinimumSize(350, 350);
    this->QWidget::resize(1200, 850);

    //Lists
    Ocean::playLists->QWidget::setMaximumWidth(250);
    Ocean::musicList->QWidget::setMaximumWidth(1500);
    Ocean::playLists->QAbstractItemView::setSelectionMode(QAbstractItemView::SingleSelection);
    Ocean::musicList->QAbstractItemView::setSelectionMode(QAbstractItemView::SingleSelection);
    Ocean::playLists->QAbstractItemView::setSelectionBehavior(QAbstractItemView::SelectRows);
    Ocean::musicList->QAbstractItemView::setSelectionBehavior(QAbstractItemView::SelectRows);
    Ocean::playLists->QWidget::setContextMenuPolicy(Qt::CustomContextMenu);
    Ocean::musicList->QWidget::setContextMenuPolicy(Qt::CustomContextMenu);

    //Slider of volume
    Ocean::sliderOfVolume->QWidget::setFixedSize(272, 17);
    //Slider of track
    Ocean::sliderOfTrack->QWidget::setMinimumWidth(225);

    //Default image of playlists
    if(Ocean::ownImage->QPixmap::load("://images/vampire_playlist.jpg", "jpg", Qt::AutoColor))
        qDebug() << "true";
    else
        qDebug() << "false";

   // Ocean::ownImage->QPixmap::scaled(150, 150, Qt::IgnoreAspectRatio, Qt::FastTransformation);
    const QPixmap *imageTTS = Ocean::ownImage;
    //TTS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    //Image of playlist
    Ocean::imageOfPlayList->QLabel::setPixmap(*imageTTS);
    Ocean::imageOfPlayList->QLabel::setAlignment(Qt::AlignTop);
    Ocean::imageOfPlayList->QObject::setObjectName("playlistImage");

    //Sort box
    Ocean::sortBy->QComboBox::addItem("music");
   /* Ocean::sortBy->QComboBox::addItem("Name");
    Ocean::sortBy->QComboBox::addItem("Date");
    Ocean::sortBy->QComboBox::addItem("Group");*/
    Ocean::sortBy->QWidget::setFixedSize(250, 35);

    //name of track
    Ocean::nameOfTrack->QWidget::setFixedHeight(35);

    //Buttons for open file
 /*   Ocean::buttonForAddMusicWithDel->QPushButton::setText("Add music with delete");
    Ocean::buttonForAddMusicOnlyCopy->QPushButton::setText("Add music with copy");
    Ocean::buttonForAddMusicWithDel->QWidget::setMinimumSize(225, 17);
    Ocean::buttonForAddMusicOnlyCopy->QWidget::setMinimumSize(225, 17);
    Ocean::buttonForAddMusicWithDel->QWidget::setMaximumSize(225, 17);
    Ocean::buttonForAddMusicOnlyCopy->QWidget::setMaximumSize(225, 17);*/

    //Buttons for player
    Ocean::stopTrack->QPushButton::setText("Stop");
    Ocean::previousTrack->QPushButton::setText("Previous");
    Ocean::nextTrack->QPushButton::setText("Next");
    Ocean::pauseTrack->QPushButton::setText("Pause");
    Ocean::playTrack->QPushButton::setText("Play");
    /*--------------------------------------------------UI--------------------------------------------------*/

    /*--------------------------------------------------MANAGERS--------------------------------------------------*/


    /*--------------------------------------------------MANAGERS--------------------------------------------------*/

    /*--------------------------------------------------TOOLS--------------------------------------------------*/
    //Timer for check widget of create playlist
    Ocean::timerForCheckWidgets->QTimer::setInterval(500);
    Ocean::timerForCheckWidgets->QTimer::start();

    //Timer for check default playlist
    Ocean::timerForCheckDefaultPlayList->QTimer::setInterval(500);
    Ocean::timerForCheckDefaultPlayList->QTimer::start();

    //Load playlists
    QStringList buffer = Ocean::GetNamesOfPlaylistsFromBinDir();

    for(QString &iter : buffer)
        iter = Ocean::playlistmanager->Playlist::ParseStringToRemoveFormatAndCurrentPath(iter);

    Ocean::playLists->QListWidget::addItems(buffer);
    qDebug() << "Load playlists" << Ocean::GetNamesOfPlaylistsFromBinDir();

    /*--------------------------------------------------TOOLS--------------------------------------------------*/


    /*
        *****!CONNECT SIGNALS WITH SLOTS!*****

    ---------------------Managers---------------------
    1)Import manager connect
        1.1) Add new music and delete it via button
        1.2) Add new music (only copy) via button
        1.3) Check added track to pass it into all songs
        1.4) Set current playlist after added new track
    2)Player manager
        2.1) play track
        2.2) pause track
        2.3) stop track
    3)Playlist manager
        3.1) next track
        3.2) previous track
        3.3) set playlist by track (set track by index)
    ---------------------Managers---------------------

    -----------------------UI-------------------------
    4)UI lists widgets
        4.1) get name of song of selected playlist (one click)
        4.2) set playlist then item double clicked
        4.3) get name of song of selected playlist (two click)
        4.4) Context Menu for playlist
        4.5) Context Menu for music list
        4.6) show songs in music list
        4.7) create widget after get name of NEW playlist
    5)Widget of create playlist
        5.1) close widget of create playlist via cancel button
        5.2) close widget of create playlist via okay button and pass QString into slot
    6) Widget for get name of playlist from user
        6.1) get name of playlist
        6.2) breake widget via cancel button
    7) Widget for get tracks to add it into new playlist
        7.1) get added tracks
        7.2) breake widget via cancel button
    -----------------------UI-------------------------

    ----------------------Tools-----------------------
    8)Timer for check CreateListWidget
        8.1) check widget of create playlist | to close it if pressed keys Alt+F4
        8.2) check widget of select playlist | to close it if pressed keys Alt+F4
        8.2) check widget of added music into playlist | to close it if pressed keys Alt+F4
    9)Timer for check default playlist 'all'
    ----------------------Tools-----------------------
    */

    //Managers-----------------------------------------
    //Import manager
 //   QObject::connect(Ocean::buttonForAddMusicWithDel, &QPushButton::clicked, Ocean::importManager, &ImportManager::CallFileDialogWithDel);
 //   QObject::connect(Ocean::buttonForAddMusicOnlyCopy, &QPushButton::clicked, Ocean::importManager, &ImportManager::CallFileDialogOnlyCopy);
    QObject::connect(Ocean::importManager, &ImportManager::CallOutToCheckSongsInsideDefaultPlayList, Ocean::playlistmanager, &Playlist::CheckDefaultPlayList);
    QObject::connect(Ocean::importManager, &ImportManager::CallOutToCheckSongsInsideDefaultPlayList, this, &Ocean::SetCurrentPlayList);
    //Player manager
    QObject::connect(Ocean::playTrack, &QPushButton::clicked, Ocean::playermanager, &QMediaPlayer::play);
    QObject::connect(Ocean::pauseTrack, &QPushButton::clicked, Ocean::playermanager, &QMediaPlayer::pause);
    QObject::connect(Ocean::stopTrack, &QPushButton::clicked, Ocean::playermanager, &QMediaPlayer::stop);
    //Playlist manager
    QObject::connect(Ocean::nextTrack, &QPushButton::clicked, Ocean::playlistmanager, &Playlist::SetNextTrack);
    QObject::connect(Ocean::previousTrack, &QPushButton::clicked, Ocean::playlistmanager, &Playlist::SetPreviousTrack);
    QObject::connect(Ocean::musicList, &QListWidget::itemDoubleClicked, this, &Ocean::SetPlayListByTrack);

    //UI-----------------------------------------------
    //UI Lists
    QObject::connect(Ocean::playLists, &QListWidget::itemClicked, this, &Ocean::GetNamesOfSongsToMusicList);
    QObject::connect(Ocean::playLists, &QListWidget::itemDoubleClicked, this, &Ocean::SetPlayList);
    QObject::connect(Ocean::playLists, &QListWidget::itemDoubleClicked, this, &Ocean::GetNamesOfSongsToMusicList);
    QObject::connect(Ocean::playLists, &QWidget::customContextMenuRequested, this, &Ocean::ShowContextMenuOfPlayList);
    QObject::connect(Ocean::musicList, &QWidget::customContextMenuRequested, this, &Ocean::ShowContextMenuOfMusicList);
    QObject::connect(this, &Ocean::CallOutPassNamesOfSongsToMusicList, this, &Ocean::PassNamesOfSongsToMusicList);
    QObject::connect(this, &Ocean::CallOutToCreateWindowThisWidgetToGetAddedTracks, this, &Ocean::CallWidgetAfterCreatePlaylistSlot);
    //Widget for get string from user (create new playlist)
    QObject::connect(Ocean::getStringFromUser, &GetStringWidget::BreakeWidget, this, &Ocean::ClosegetStringFromUserViaCancel);
    QObject::connect(Ocean::getStringFromUser, &GetStringWidget::SendName, this, &Ocean::ClosegetStringFromUserViaOkay);
    //Widget for get name of playlist from user
    QObject::connect(Ocean::getStringWithSelectedPlaylist, &SelectPlaylist::CallOutToPassStringFromWidget, this, &Ocean::ParseMusicList);
    QObject::connect(Ocean::getStringWithSelectedPlaylist, &SelectPlaylist::BreakeWidget, this, &Ocean::ClosegetStringWithSelectedPlaylistViaCancel);
    //Widget for get string list with added tracks
    QObject::connect(Ocean::getAddedTracksFromWidget, &AddMusicWidget::SendListWithSongs, this, &Ocean::PassAddedTracksIntoBuffer);
    QObject::connect(Ocean::getAddedTracksFromWidget, &AddMusicWidget::BreakeWidget, this, &Ocean::ClosegetAddedTracksFromWidgetViaCancel);

    //Tools--------------------------------------------
    //Timer for check widgets in progress
    QObject::connect(Ocean::timerForCheckWidgets, &QTimer::timeout, this, &Ocean::IfgetStringFromUserClosed);
    QObject::connect(Ocean::timerForCheckWidgets, &QTimer::timeout, this, &Ocean::IfgetStringWithSelectedPlaylistClosed);
    QObject::connect(Ocean::timerForCheckWidgets, &QTimer::timeout, this, &Ocean::IfgetAddedTracksFromWidgetClosed);
    //Timer for check default playlist (inside Ocean::playLists zero iter "all")
    QObject::connect(Ocean::timerForCheckDefaultPlayList, &QTimer::timeout, this, &Ocean::WriteDefaultPlayList);

    //---------------------------------------------SYSTEM INFO
    qDebug() << "SYSTEM INFO";

    qDebug() << "importManager hex: " << hex << importManager;
    qDebug() << "playlistmanager hex: " << hex << playlistmanager;
    qDebug() << "playermanager hex: " << hex << playermanager;
    //---------------------------------------------SYSTEM INFO

    return;
}

Ocean::~Ocean()
{
    qDebug() << "Destructor from Ocean.cpp";

    //Tools
    sysmanager->Free(timerForCheckWidgets);
    sysmanager->Free(timerForCheckDefaultPlayList);
    sysmanager->Free(cd);

    //---------------------------------------------SYSTEM INFO
    qDebug() << "SYSTEM INFO";

    if(sysmanager->PointerIsEmpty(timerForCheckWidgets))
        qDebug() << "timerForCheckWidgets empty!";

    if(sysmanager->PointerIsEmpty(timerForCheckDefaultPlayList))
        qDebug() << "timerForCheckDefaultPlayList empty!";

    if(sysmanager->PointerIsEmpty(cd))
        qDebug() << "cd empty!";
    //---------------------------------------------SYSTEM INFO

    //Own classes
    //managers
    sysmanager->Free(importManager);
    sysmanager->Free(playlistmanager);
    sysmanager->Free(playermanager);

    //---------------------------------------------SYSTEM INFO
    qDebug() << "SYSTEM INFO";

    if(sysmanager->PointerIsEmpty(importManager))
        qDebug() << "importManager empty!";

    if(sysmanager->PointerIsEmpty(playlistmanager))
        qDebug() << "playlistmanager empty!";

    if(sysmanager->PointerIsEmpty(playermanager))
        qDebug() << "playermanager empty!";
    //---------------------------------------------SYSTEM INFO

    //widgets
    sysmanager->Free(getAddedTracksFromWidget);
    sysmanager->Free(getStringFromUser);
    sysmanager->Free(getStringWithSelectedPlaylist);

    //---------------------------------------------SYSTEM INFO
    qDebug() << "SYSTEM INFO";

    if(sysmanager->PointerIsEmpty(getAddedTracksFromWidget))
        qDebug() << "getAddedTracksFromWidget empty!";

    if(sysmanager->PointerIsEmpty(getStringFromUser))
        qDebug() << "getStringFromUser empty!";

    if(sysmanager->PointerIsEmpty(getStringWithSelectedPlaylist))
        qDebug() << "getStringWithSelectedPlaylist empty!";
    //---------------------------------------------SYSTEM INFO

    //UI
    sysmanager->Free(ownImage);
    sysmanager->Free(spacer);
    sysmanager->Free(sortBy);
    sysmanager->Free(imageOfPlayList);
    sysmanager->Free(sliderOfTrack);
    sysmanager->Free(sliderOfVolume);
    sysmanager->Free(playLists);
    sysmanager->Free(musicList);
    sysmanager->Free(playTrack);
    sysmanager->Free(pauseTrack);
    sysmanager->Free(stopTrack);
    sysmanager->Free(nextTrack);
    sysmanager->Free(previousTrack);
//    sysmanager->Free(buttonForAddMusicWithDel);
//    sysmanager->Free(buttonForAddMusicOnlyCopy);
    sysmanager->Free(ui);

    //system
    delete sysmanager;
    sysmanager = nullptr;

    qDebug() << "SYSTEM INFO";

    if(!sysmanager)
        qDebug() << "sysmanager empty!";

    return;
}


/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*||||||||||||||||||||||||||||||||||||||||||||||||||this->QWidget||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||Events for MainWindow|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
void Ocean::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    int short h = event->QResizeEvent::size().QSize::height();
    int short w = event->QResizeEvent::size().QSize::width();

    if((h <= 200) || (w <= 400))
        Ocean::Hidder();
    else
        Ocean::Shower();

    return;
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||Events for MainWindow|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||Slots for MainWindow||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
void Ocean::Hidder()
{
    Ocean::spacer->QSpacerItem::changeSize(0, 0);
    Ocean::playLists->QWidget::hide();
    Ocean::musicList->QWidget::hide();
    Ocean::sortBy->QWidget::hide();
//    Ocean::buttonForAddMusicWithDel->QWidget::hide();
//    Ocean::buttonForAddMusicOnlyCopy->QWidget::hide();

    return;
}

void Ocean::Shower()
{
    Ocean::spacer->QSpacerItem::changeSize(100, 250);
    Ocean::playLists->QWidget::show();
    Ocean::musicList->QWidget::show();
    Ocean::sortBy->QWidget::show();
 //   Ocean::buttonForAddMusicWithDel->QWidget::show();
 //   Ocean::buttonForAddMusicOnlyCopy->QWidget::show();

    return;
}

void Ocean::GetNamesOfSongsToMusicList(QListWidgetItem *item)
{
    Ocean::musicList->QListWidget::clear();

    emit this->Ocean::CallOutPassNamesOfSongsToMusicList(Ocean::playlistmanager->Playlist::GetSongsFromCurrentPlayList(item->QListWidgetItem::text() + ".m3u8"));

    return;
}

void Ocean::PassNamesOfSongsToMusicList(const QStringList &songs)
{
    QStringList buffer = songs;

    for(QString &iter : buffer)
        iter = Ocean::playlistmanager->Playlist::ParseStringToRemoveFormatAndCurrentPath(iter);

    Ocean::musicList->QListWidget::clear();
    Ocean::musicList->QListWidget::addItems(buffer);

    return;
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||Slots for MainWindow||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/


/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*||||||||||||||||||||||||||||||||||||||||||||||||||this->QWidget||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/



/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||MANAGERS||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||Context Menu of Music list|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
void Ocean::ShowContextMenuOfMusicList(const QPoint &point)
{
    QPoint globalPoint = Ocean::playLists->QWidget::mapToGlobal(point);

    QMenu myMenu;
    myMenu.QMenu::addAction("Add with delete", Ocean::importManager, &ImportManager::CallFileDialogWithDel);
    myMenu.QMenu::addAction("Add with copy", Ocean::importManager, &ImportManager::CallFileDialogOnlyCopy);
    myMenu.QMenu::addAction("Add to...", this, SLOT(AddSongIntoPlayListByIndex()));
    myMenu.QMenu::addAction("Delete", this, SLOT(EraseItemFromMusicList()));
    myMenu.QMenu::addAction("Delete All", this, SLOT(EraseAllItemsFromMusicList()));

    myMenu.QMenu::exec(globalPoint);

    return;
}

void Ocean::EraseAllItemsFromMusicList()
{
    Ocean::musicList->QListWidget::clear();

    for(unsigned short int iter = 0; iter < Ocean::playLists->QListWidget::selectedItems().QList::size(); ++iter)
    {
        QListWidgetItem *item = Ocean::playLists->QListWidget::item(Ocean::playLists->QListWidget::currentRow());

        if(item->text() == Ocean::playlistmanager->Playlist::GetCurrentPlayListName())
        {
            Ocean::playermanager->QMediaPlayer::stop();
            emit Ocean::playlistmanager->Playlist::CallOutRemoveAllTracksFromCurrentPlayList();
            emit this->Ocean::CallOutPassNamesOfSongsToMusicList(Ocean::playlistmanager->Playlist::GetSongsFromCurrentPlayList(item->QListWidgetItem::text() + ".m3u8"));
        }
        else
        {
            emit Ocean::playlistmanager->Playlist::CallOutRemoveAllTracksFromPlayListByName(item->text());
            emit this->Ocean::CallOutPassNamesOfSongsToMusicList(Ocean::playlistmanager->Playlist::GetSongsFromCurrentPlayList(item->QListWidgetItem::text() + ".m3u8"));
        }

        item = nullptr;
    }

    return;
}

void Ocean::EraseItemFromMusicList()
{
    // If multiple selection is on, we need to erase all selected items
    for (unsigned short int iter = 0; iter < Ocean::musicList->QListWidget::selectedItems().QList::size(); ++iter)
    {
        // Get curent item on selected row
        QListWidgetItem *item = Ocean::musicList->QListWidget::item(Ocean::musicList->QListWidget::currentRow());

        //return if item empty
        if(item->text() == "")
            return;

        for(unsigned short int iterPlayList = 0; iterPlayList < Ocean::playLists->QListWidget::selectedItems().QList::size(); ++iterPlayList)
        {
            QListWidgetItem *playlistIter = Ocean::playLists->QListWidget::item(Ocean::playLists->QListWidget::currentRow());

            if(playlistIter->QListWidgetItem::text() == Ocean::playlistmanager->Playlist::GetCurrentPlayListName())
            {
                //remove from current playlist
                emit Ocean::playlistmanager->Playlist::CallOutRemoveTrackFromCurrentPlayListByIndex(Ocean::musicList->QListWidget::currentRow());
                emit this->Ocean::CallOutPassNamesOfSongsToMusicList(Ocean::playlistmanager->Playlist::GetSongsFromCurrentPlayList(Ocean::playlistmanager->Playlist::GetCurrentPlayListName() + ".m3u8"));
            }
            else
            {
                //remove from other playlist
                emit Ocean::playlistmanager->Playlist::CallOutRemoveTrackFromPlayListByIndex(Ocean::musicList->QListWidget::currentRow(), playlistIter->text());
                emit this->Ocean::CallOutPassNamesOfSongsToMusicList(Ocean::playlistmanager->Playlist::GetSongsFromCurrentPlayList(playlistIter->text() + ".m3u8"));
            }
        }
    }

    return;
}

void Ocean::AddSongIntoPlayListByIndex()
{
    Ocean::getStringWithSelectedPlaylist->SelectPlaylist::PassAllPlaylistsIntoWidget(Ocean::GetAllItemsFromList());

    this->QWidget::setDisabled(true);
    Ocean::getStringWithSelectedPlaylist->QWidget::show();

    return;
}

void Ocean::ParseMusicList(const QString &name)
{
    //selected item of music list
    for (unsigned short int iter = 0; iter < musicList->selectedItems().size(); ++iter)
    {
        QListWidgetItem *trackCurrent = musicList->item(musicList->currentRow());

        //current item of playlist
        for (unsigned short int iter = 0; iter < playLists->selectedItems().size(); ++iter)
        {
            QListWidgetItem *playlistCurrent = playLists->item(playLists->currentRow());

            emit playlistmanager->CallOutAddSongIntoPlayList(trackCurrent->text(), //name of song
                                                                    name, //selected playlist
                                                                    playlistCurrent->text(), //current playlist
                                                                    musicList->currentRow()); //index of song
        }
    }

    return;
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||Context Menu of Music list|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||Context Menu of Playlists||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
void Ocean::ShowContextMenuOfPlayList(const QPoint &point)
{
    QPoint globalPoint = Ocean::playLists->QWidget::mapToGlobal(point);

    // Create menu and insert some actions
    QMenu myMenu;
    myMenu.QMenu::addAction("Create", this, SLOT(CreatePlaylist()));
    myMenu.QMenu::addAction("Delete", this, SLOT(EraseItemFromPlayList()));
    myMenu.QMenu::addAction("Rename", this, SLOT(RenamePlaylist()));
    //myMenu.QMenu::addAction("Save", ..., ...);
    //myMenu.QMenu::addAction("Import", ..., ...);
    // Show context menu at handling position
    myMenu.QMenu::exec(globalPoint);

    return;
}

void Ocean::EraseItemFromPlayList()
{
    for (unsigned short int iter = 0; iter < Ocean::playLists->QListWidget::selectedItems().QList::size(); ++iter)
    {
        QListWidgetItem *item = Ocean::playLists->QListWidget::item(Ocean::playLists->QListWidget::currentRow());

        if(item->text() == "all")
            return;

        if(item->text() == Ocean::playlistmanager->GetCurrentPlayListName())
        {
            //clear current playlist
            Ocean::musicList->QListWidget::clear();
            Ocean::playlistmanager->Playlist::GetCurrentPlayList()->QMediaPlaylist::clear();
            Ocean::playermanager->QMediaPlayer::stop();
        }

        Ocean::playlistmanager->Playlist::CallOutRemovePlayListByName(item->text());

        delete item;
    }

    return;
}

void Ocean::CreatePlaylist()
{
    this->QWidget::setDisabled(true);
    Ocean::getStringFromUser->QWidget::show();

    return;
}

//TTS
void Ocean::RenamePlaylist()
{
    for(unsigned short int iter = 0; iter < Ocean::playLists->QListWidget::selectedItems().size(); ++iter)
    {
        // Get curent item on selected row
        QListWidgetItem *item = Ocean::playLists->QListWidget::item(Ocean::playLists->QListWidget::currentRow());

        QString buffer = "";

        if((item->text() == "") || (item->text() == "all"))
            return;
        else
        {
            buffer = item->text();
            Ocean::playLists->QListWidget::editItem(item);
        }

        Ocean::Rename(item, buffer);
    }

    return;
}

//TTS
void Ocean::Rename(const QListWidgetItem *item, QString buffer)
{
    item->text() == Ocean::playlistmanager->Playlist::GetCurrentPlayListName() ?
    emit Ocean::playlistmanager->Playlist::CallOutRenameCurrentPlayList(item->text(), Ocean::playlistmanager->Playlist::GetCurrentPlayList()) :
    emit Ocean::playlistmanager->Playlist::CallOutRenameSelectedPlayList(buffer, item->text());

    return;
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||Context Menu of Playlists||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||Set PLAYLIST|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/

void Ocean::SetPlayList(QListWidgetItem *item)
{
    //set name of playlist
    emit Ocean::playlistmanager->Playlist::CallOutSetCurrentPlayListName(item->QListWidgetItem::text());

    //clear current playlist
    Ocean::playlistmanager->Playlist::GetCurrentPlayList()->QMediaPlaylist::clear();

    //load
    if(Ocean::playlistmanager->Playlist::LoadPlayList(Ocean::playlistmanager->Playlist::GetCurrentPlayListName()))
    {
        Ocean::playermanager->QMediaPlayer::setPlaylist(Ocean::playlistmanager->Playlist::GetCurrentPlayList());
        Ocean::playermanager->QMediaPlayer::play();
    }

    //show songs in music list
    emit this->Ocean::CallOutPassNamesOfSongsToMusicList(Ocean::playlistmanager->Playlist::GetSongsFromCurrentPlayList(item->QListWidgetItem::text() + ".m3u8"));

    return;
}

void Ocean::SetPlayListByTrack(QListWidgetItem *item)
{
    for(unsigned short int iterPlayList = 0; iterPlayList < Ocean::playLists->QListWidget::selectedItems().QList::size(); ++iterPlayList)
    {
        //playlist
        QListWidgetItem *iter = Ocean::playLists->QListWidget::item(Ocean::playLists->QListWidget::currentRow());

        //set name of playlist
        emit Ocean::playlistmanager->Playlist::CallOutSetCurrentPlayListName(iter->QListWidgetItem::text());

        //clear current playlist
        Ocean::playlistmanager->Playlist::GetCurrentPlayList()->QMediaPlaylist::clear();

        //load
        if(Ocean::playlistmanager->Playlist::LoadPlayList(Ocean::playlistmanager->Playlist::GetCurrentPlayListName()))
        {
            Ocean::playermanager->QMediaPlayer::setPlaylist(Ocean::playlistmanager->Playlist::GetCurrentPlayList());
            Ocean::playermanager->QMediaPlayer::play();

            //set track by index and play it
            const int index = item->QListWidgetItem::listWidget()->QListWidget::row(item);
            Ocean::playlistmanager->Playlist::SetTrackByIndex(index);
        }

        //show songs in music list
        emit this->Ocean::CallOutPassNamesOfSongsToMusicList(Ocean::playlistmanager->Playlist::GetSongsFromCurrentPlayList(iter->QListWidgetItem::text() + ".m3u8"));
    }

    return;
}

void Ocean::SetCurrentPlayList()
{
    if(Ocean::playlistmanager->Playlist::GetCurrentPlayListName() == "all")
    {
        qDebug() << "!!!!!!!!!!!!!!!!position " << Ocean::playermanager->Player::GetPositionOfTrack();

        const unsigned short int index = Ocean::playlistmanager->Playlist::GetCurrentPlayList()->QMediaPlaylist::currentIndex();
        QString nameOfSongBuffer = "";

        //save current track by name
        for(unsigned short int iter = 0; iter < Ocean::musicList->QListWidget::count(); ++iter)
            if(iter == index)
                nameOfSongBuffer = Ocean::musicList->QListWidget::item(index)->QListWidgetItem::text();

        //clear current playlist
        Ocean::playlistmanager->Playlist::GetCurrentPlayList()->QMediaPlaylist::clear();

        //load
        if(Ocean::playlistmanager->Playlist::LoadPlayList(Ocean::playlistmanager->Playlist::GetCurrentPlayListName()))
        {
            //set playlist
            Ocean::playermanager->QMediaPlayer::setPlaylist(Ocean::playlistmanager->Playlist::GetCurrentPlayList());

            //show songs in music list
            emit this->Ocean::CallOutPassNamesOfSongsToMusicList(Ocean::playlistmanager->Playlist::GetSongsFromCurrentPlayList("all.m3u8"));

            //index for set last track by index
            unsigned short int newIndex = 0;

            //find current track
            for(unsigned short int iter = 0; iter < Ocean::musicList->QListWidget::count(); ++iter)
            {
                QString bufferOfTrackName = Ocean::musicList->QListWidget::item(iter)->QListWidgetItem::text();

                if(nameOfSongBuffer == bufferOfTrackName)
                    newIndex = iter;
            }

            //set current track
            Ocean::playlistmanager->Playlist::GetCurrentPlayList()->QMediaPlaylist::setCurrentIndex(newIndex);
            //play this track
            Ocean::playermanager->QMediaPlayer::play();
            //set current position
            Ocean::playermanager->Player::SetPositionOfTrack(Ocean::playermanager->Player::GetPositionOfTrack());
        }
    }

    return;
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||Set PLAYLIST|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/

/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||MANAGERS||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/



/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||UI|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||GET STRING WIDGET|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
void Ocean::ClosegetStringFromUserViaCancel()
{
    this->QWidget::setEnabled(true);
    Ocean::getStringFromUser->QWidget::hide();

    return;
}

void Ocean::ClosegetStringFromUserViaOkay()
{
    this->QWidget::setEnabled(true);
    Ocean::getStringFromUser->QWidget::hide();

    //create widget to add tracks into new playlist
    emit this->Ocean::CallOutToCreateWindowThisWidgetToGetAddedTracks();

    return;
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||GET STRING WIDGET|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||SELECT PLAYLIST|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
void Ocean::ClosegetStringWithSelectedPlaylist()
{
    this->QWidget::setEnabled(true);
    Ocean::getStringWithSelectedPlaylist->QWidget::hide();

    return;
}

void Ocean::ClosegetStringWithSelectedPlaylistViaCancel()
{
    this->QWidget::setEnabled(true);
    Ocean::getStringWithSelectedPlaylist->QWidget::hide();

    return;
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||SELECT PLAYLIST|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||Widget for get added tracks from widget|||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
void Ocean::ClosegetAddedTracksFromWidgetViaCancel()
{
    this->QWidget::setEnabled(true);
    Ocean::getAddedTracksFromWidget->QWidget::hide();

    return;
}

void Ocean::PassAddedTracksIntoBuffer(const QStringList &list)
{
    Ocean::bufferOfAddedTracks.QStringList::clear();
    Ocean::bufferOfAddedTracks += list;

    Ocean::playLists->QListWidget::addItem(Ocean::getStringFromUser->GetStringWidget::GetNameOfNewPlayList()); //add new playlist

    //create new playlist
    emit Ocean::playlistmanager->Playlist::CallOutCreateNewPlayList(Ocean::getStringFromUser->GetStringWidget::GetNameOfNewPlayList(),
                                                                    Ocean::playlistmanager->Playlist::ParseToGetFullPathOfTracks(Ocean::bufferOfAddedTracks));

    this->QWidget::setEnabled(true);
    Ocean::getAddedTracksFromWidget->QWidget::hide();

    return;
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||Widget for get added tracks from widget|||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/

/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||UI|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/



/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||Tools||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

void Ocean::IfgetStringFromUserClosed()
{
    if(Ocean::getStringFromUser->QWidget::isHidden())
        this->QWidget::setEnabled(true);
    else
        this->QWidget::setDisabled(true);

    return;
}

void Ocean::IfgetStringWithSelectedPlaylistClosed()
{
    if(Ocean::getStringWithSelectedPlaylist->QWidget::isHidden())
        this->QWidget::setEnabled(true);
    else
        this->QWidget::setDisabled(true);

    return;
}

void Ocean::IfgetAddedTracksFromWidgetClosed()
{
    if(Ocean::getAddedTracksFromWidget->QWidget::isHidden())
        this->QWidget::setEnabled(true);
    else
        this->QWidget::setDisabled(true);

    return;
}

QStringList Ocean::GetNamesOfPlaylistsFromBinDir()
{
    Ocean::cd->QDir::setCurrent(QCoreApplication::applicationDirPath() + "/bin/");
    QStringList playlists = cd->QDir::entryList(QStringList() << "*.m3u8" << "*.M3U8", QDir::Files);
    Ocean::cd->QDir::setCurrent(QCoreApplication::applicationDirPath());

    return playlists;
}

void Ocean::CallWidgetAfterCreatePlaylistSlot()
{
    QStringList buffer = Ocean::playlistmanager->Playlist::GetAllTracks();

    for(QString &iter : buffer)
        iter = Ocean::playlistmanager->Playlist::ParseStringToRemoveFormatAndCurrentPath(iter);

    Ocean::getAddedTracksFromWidget->AddMusicWidget::GetAllSongsfFromMainWindow(buffer);
    this->QWidget::setDisabled(true);
    Ocean::getAddedTracksFromWidget->QWidget::show();

    return;
}

void Ocean::WriteDefaultPlayList()
{
    if(Ocean::playLists->QListWidget::item(0)->QListWidgetItem::text() == "all")
        return;
    else
        Ocean::playLists->QListWidget::addItem("all");

    return;
}

/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||Tools||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/



/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||METHODS FOR UI||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

QStringList Ocean::GetAllItemsFromList()
{
    QStringList list;

    for(unsigned short int iter = 0; iter < Ocean::playLists->QListWidget::count(); ++iter)
    {
        QListWidgetItem* item = Ocean::playLists->item(iter);
        list.QStringList::push_back(item->text());
    }

    return  list;
}

/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||METHODS FOR UI||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
