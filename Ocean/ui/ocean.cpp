/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#include "ui/ocean.h"

using namespace Qt;
using namespace std;

Ocean::Ocean(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Ocean)
{
    ui->setupUi(this);

    //ALLOCATE MEMORY
    try
    {
        //Objects of UI
        spacer = new QSpacerItem(200, 0);
        ownImage = new QPixmap();
        imageOfPlayList = new QLabel(this);
        nameOfTrack = new QLabel(this);
        sliderOfTrack = new Slider(this);
        sliderOfVolume = new Slider(this, 100);
        playLists = new CustomListWidget(this);
        musicList = new CustomListWidget(this);
        pausePlayTrack = new Button(this, "pause");
        stopTrack = new Button(this, "stop");
        nextTrack = new Button(this, "next");
        previousTrack = new Button(this, "previous");
        playbackMode = new Button(this, "cross");
        errorMessageBox = new QMessageBox(this);

        //Tools for widgets
        timerForCheckWidgets = new QTimer(this);
        timerForCheckDefaultPlayList = new QTimer(this);
        cd = new QDir();

        //Shortcuts for tracks
        ctrlD = new QShortcut(this);
        ctrlR = new QShortcut(this);
        //Shortcuts for playlists
        previuseSong = new QShortcut(this);
        pauseSong = new QShortcut(this);
        nextSong = new QShortcut(this);
        //Shortcuts for window of app
        shiftF = new QShortcut(this);
        shiftQ = new QShortcut(this);
        shiftH = new QShortcut(this);
        //Shortcuts for move track up or down inside playlist
        moveTrackUp = new QShortcut(this);
        moveTrackDown = new QShortcut(this);

        //Object of own classes
        //widgets
        getAddedTracksFromWidget = new AddMusicWidget();
        getStringFromUserToCreateNewPlaylist = new GetStringWidget();
        getStringFromUserToRenamePlaylist = new GetStringWidget();
        getStringFromUserToRenameTrack = new GetStringWidget();
        getStringWithSelectedPlaylist = new SelectPlaylist();
        //managers
        importManager = new ImportManager(this);
        playlistmanager = new Playlist(this);
        playermanager = new Player(this);
    }
    catch(...)
    {
        qCritical() << "Some exception caught";
        exit(1);
    }

    /*--------------------------------------------------UI--------------------------------------------------*/
    //UpSide
    //Player
    ui->playSlider->addWidget(nameOfTrack);
    ui->playSlider->addWidget(sliderOfTrack);
    ui->playSlider->setAlignment(nameOfTrack, AlignJustify);

    //Left side
    //Music
    ui->music->addWidget(playLists);
    ui->music->addWidget(musicList);

    //Right side
    //Image of play list
    ui->image->addWidget(imageOfPlayList);
    ui->volumeSlider->addWidget(sliderOfVolume);
    ui->buttonsOfTracks->addWidget(previousTrack);
    ui->buttonsOfTracks->addWidget(stopTrack);
    ui->buttonsOfTracks->addWidget(pausePlayTrack);
    ui->buttonsOfTracks->addWidget(playbackMode);
    ui->buttonsOfTracks->addWidget(nextTrack);
    ui->tool->setAlignment(AlignTop);
    //slider for volume

    //Main window  
    this->setMinimumSize(270, 420);
    this->resize(1000, 750);

    //Lists
    playLists->setMaximumWidth(250);
    musicList->setMaximumWidth(1500);

    //Slider of volume
    sliderOfVolume->setFixedSize(250, 17);
    //Slider of track
    sliderOfTrack->setMinimumWidth(250);

    //buttons
    pausePlayTrack->SetIconForSwitch("play");
    //Default image of playlists
    ownImage->load("://images/vampire_playlist.jpg", "jpg", AutoColor);

    const QPixmap *imageTTS = ownImage;


    //Image of playlist
    imageOfPlayList->setScaledContents(true);
    imageOfPlayList->setFixedSize(250, 270);
    imageOfPlayList->setPixmap(*imageTTS);
    imageOfPlayList->setAlignment(AlignTop);
    imageOfPlayList->setObjectName("playlistImage");

    //name of track
    nameOfTrack->setFixedHeight(35);
    nameOfTrack->setObjectName("nameOfTrack");

    //Error message box
    errorMessageBox->setWindowTitle("Error");
    errorMessageBox->setWindowModality(ApplicationModal); //block all UI windows
    errorMessageBox->setIcon(QMessageBox::Critical); //error icon
    /*--------------------------------------------------UI--------------------------------------------------*/

    /*--------------------------------------------------MANAGERS--------------------------------------------------*/


    /*--------------------------------------------------MANAGERS--------------------------------------------------*/

    /*--------------------------------------------------TOOLS--------------------------------------------------*/
    //Timer for check widget of create playlist
    timerForCheckWidgets->setInterval(500);
    timerForCheckWidgets->start();

    //Timer for check default playlist
    timerForCheckDefaultPlayList->setInterval(500);
    timerForCheckDefaultPlayList->start();

    //Load playlists
    QStringList buffer = this->GetNamesOfPlaylistsFromBinDir();

    //Parsing names of playlists to show inside UI without format of files
    for(QString &iter : buffer)
        iter = playlistmanager->ParseStringToRemoveFormatAndCurrentPath(iter);

    //Load playlists
    playLists->addItems(buffer);
    /*--------------------------------------------------TOOLS--------------------------------------------------*/


    /*-------------------------------------------------Shortcut------------------------------------------------*/
    //Shortcuts for tracks
    ctrlD->setKey(CTRL + Key_D);
    ctrlR->setKey(CTRL + Key_R);
    //Shortcuts for playlists
    previuseSong->setKey(Key_Left);
    pauseSong->setKey(Key_Space);
    nextSong->setKey(Key_Right);
    //Shortcuts for window of app
    shiftF->setKey(SHIFT + Key_F);
    shiftQ->setKey(SHIFT + Key_Q);
    shiftH->setKey(SHIFT + Key_H);
    //Shortcuts for move track up or down inside playlist
    moveTrackUp->setKey(CTRL + Key_Up);
    moveTrackDown->setKey(CTRL + Key_Down);
    /*-------------------------------------------------Shortcut------------------------------------------------*/

    /*
        *****!CONNECT SIGNALS WITH SLOTS!*****

    ---------------------Managers---------------------
    1)Import manager connect
        1.1) Check added track to pass it into all songs
        1.2) Set current playlist after added new track
        1.3) Add files via Drag and Drop into app after that (into current playlist or by name)
        1.4) Add playlist files via Drag and Drop into app after that
    2)Player manager
        2.1) play track/pause track
        2.2) stop track
        2.3) error checker
    3)Playlist manager
        3.1) next track
        3.2) previous track
        3.3) set playback mode of playlist
        3.4) set playlist by track (set track by index)
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
    7) Widget for get name of playlist from user
        7.1) get name of track
        7.2) breake widget via cancel button
    8) Widget for get tracks to add it into new playlist
        8.1) get added tracks
        8.2) breake widget via cancel button
    9) Message box with error by playlist
        9.1) Show message box
        9.2) Close message box
    -----------------------UI-------------------------

    ----------------------Tools-----------------------
    9)Timer for check CreateListWidget
        9.1) check widget of create playlist | to close it if pressed keys Alt+F4
        9.2) check widget of select playlist | to close it if pressed keys Alt+F4
        9.3) check widget of added music into playlist | to close it if pressed keys Alt+F4
        9.4) check widget of added music into playlist | to close it if pressed keys Alt+F4
    10)Timer for check default playlist 'all'
    ----------------------Tools-----------------------

    --------------------Shortcut----------------------
    11)Shortcuts for work with tracks, player and window of app
        11.1) Trigger delete track Ctrl + D
        11.2) Trigger rename track Ctrl + R

        11.3) Trigger previuse track A
        11.4) Trigger play or pause S
        11.5) Trigger next track D

        11.6) Trigger Full Window Shift + F
        11.7) Trigger Quit Window Shift + Q
        11.8) Trigger Hide Window Shift + H

        11.9) Trigger move track up CTRL + KEY UP
        11.10) Trigger move track down CTRL + KEY DOWN
    --------------------Shortcut----------------------
    */

    //Managers-----------------------------------------
    //Import manager
    connect(importManager, &ImportManager::CallOutToCheckSongsInsideDefaultPlayList, playlistmanager, &Playlist::CheckDefaultPlayList);
    connect(importManager, &ImportManager::CallOutToCheckSongsInsideDefaultPlayList, this, &Ocean::SetCurrentPlayList);
    connect(musicList, &CustomListWidget::CallOutItemsDroped, this, &Ocean::AddFilesAfterDropEvent);

    //Player manager
    connect(pausePlayTrack, &QPushButton::clicked, playermanager, &Player::SetPausePlayTrack);
    connect(playermanager, &Player::CallOutSetImagePuasePlayTrack, pausePlayTrack, &Button::changeIcon);
    connect(stopTrack, &QPushButton::clicked, playermanager, &QMediaPlayer::stop);
    connect(sliderOfVolume, &QSlider::valueChanged, playermanager,&QMediaPlayer::setVolume);
    connect(sliderOfTrack, &QSlider::valueChanged, playermanager,&QMediaPlayer::setPosition);

    //Playlist manager
    connect(nextTrack, &QPushButton::clicked, playlistmanager, &Playlist::SetNextTrack);
    connect(previousTrack, &QPushButton::clicked, playlistmanager, &Playlist::SetPreviousTrack);
    connect(playbackMode, &QPushButton::clicked, playlistmanager, &Playlist::SetModOfPlayback);
    connect(musicList, &QListWidget::itemDoubleClicked, this, &Ocean::SetPlayListByTrack);
    connect(playlistmanager, &Playlist::CallOutSetNameOfCurrentTrack, this, &Ocean::SetNameOfCurrentTrackFromPlaylist);

    //UI-----------------------------------------------
    //UI Lists
    connect(playLists, &QListWidget::itemClicked, this, &Ocean::GetNamesOfSongsToMusicList);
    connect(playLists, &QListWidget::itemDoubleClicked, this, &Ocean::SetPlayList);
    connect(playLists, &QListWidget::itemDoubleClicked, this, &Ocean::GetNamesOfSongsToMusicList);
    connect(playLists, &QWidget::customContextMenuRequested, this, &Ocean::ShowContextMenuOfPlayList);
    connect(musicList, &QWidget::customContextMenuRequested, this, &Ocean::ShowContextMenuOfMusicList);
    connect(this, &Ocean::CallOutPassNamesOfSongsToMusicList, this, &Ocean::PassNamesOfSongsToMusicList);
    connect(this, &Ocean::CallOutToCreateWindowThisWidgetToGetAddedTracks, this, &Ocean::CallWidgetAfterCreatePlaylistSlot);
    //Widget for get string from user (create new playlist)
    connect(getStringFromUserToCreateNewPlaylist, &GetStringWidget::BreakeWidget, this, &Ocean::ClosegetStringFromUserViaCancel);
    connect(getStringFromUserToCreateNewPlaylist, &GetStringWidget::SendName, this, &Ocean::ClosegetStringFromUserToCreatePlaylist);
    //Widget for get string from user (rename playlist)
    connect(getStringFromUserToRenamePlaylist, &GetStringWidget::BreakeWidget, this, &Ocean::ClosegetStringFromUserToRenameViaCancel);
    connect(getStringFromUserToRenamePlaylist, &GetStringWidget::SendName, this, &Ocean::Rename);
    //Widget for get string from user (rename track)
    connect(getStringFromUserToRenameTrack, &GetStringWidget::BreakeWidget, this, &Ocean::ClosegetStringFromUserToRenameTrackViaCancel);
    connect(getStringFromUserToRenameTrack, &GetStringWidget::SendName, this, &Ocean::RenameTrackByNewName);
    //Widget for get name of playlist from user
    connect(getStringWithSelectedPlaylist, &SelectPlaylist::CallOutToPassStringFromWidget, this, &Ocean::ParseMusicList);
    connect(getStringWithSelectedPlaylist, &SelectPlaylist::BreakeWidget, this, &Ocean::ClosegetStringWithSelectedPlaylistViaCancel);
    //Widget for get string list with added tracks
    connect(getAddedTracksFromWidget, &AddMusicWidget::SendListWithSongs, this, &Ocean::PassAddedTracksIntoBuffer);
    connect(getAddedTracksFromWidget, &AddMusicWidget::BreakeWidget, this, &Ocean::ClosegetAddedTracksFromWidgetViaCancel);
    //Error message box by playlist
    connect(playlistmanager, &Playlist::CallOutErrorMessage, this, &Ocean::ErrorsByPlaylist);
    connect(errorMessageBox, &QMessageBox::buttonClicked, errorMessageBox, &QMessageBox::exec);

    //Tools--------------------------------------------
    //Timer for check widgets in progress
    connect(timerForCheckWidgets, &QTimer::timeout, this, &Ocean::IfgetStringFromUserClosed);
    connect(timerForCheckWidgets, &QTimer::timeout, this, &Ocean::IfgetStringWithSelectedPlaylistClosed);
    connect(timerForCheckWidgets, &QTimer::timeout, this, &Ocean::IfgetAddedTracksFromWidgetClosed);
    connect(timerForCheckWidgets, &QTimer::timeout, this, &Ocean::IfgetStringFromUserToRenameClosed);
    //Timer for check default playlist (inside Ocean::playLists zero iter "all")
    connect(timerForCheckDefaultPlayList, &QTimer::timeout, this, &Ocean::WriteDefaultPlayList);

    //Shortcuts-----------------------------------------
    //Keys for work with tracks
    connect(ctrlD, &QShortcut::activated, this, &Ocean::EraseItemFromMusicList);
    connect(ctrlR, &QShortcut::activated, this, &Ocean::RenameTrack);
    //Keys for work with player
    connect(previuseSong, &QShortcut::activated, playlistmanager, &Playlist::SetPreviousTrack);
    connect(pauseSong, &QShortcut::activated, playermanager, &Player::SetPausePlayTrack);
    connect(nextSong, &QShortcut::activated, playlistmanager, &Playlist::SetNextTrack);
    //Keys for work with app fo window
    connect(shiftF, &QShortcut::activated, this, &Ocean::FullViaShiftF);
    connect(shiftQ, &QShortcut::activated, this, &Ocean::QuitViaShiftQ);
    connect(shiftH, &QShortcut::activated, this, &Ocean::HideViaShiftH);
    //Shortcuts for move track up or down inside playlist
    connect(moveTrackUp, &QShortcut::activated, this, &Ocean::MoveTrackUp);
    connect(moveTrackDown, &QShortcut::activated, this, &Ocean::MoveTrackDown);
    connect(moveTrackUp, &QShortcut::activated, this, &Ocean::SetCurrentPlayList);
    connect(moveTrackDown, &QShortcut::activated, this, &Ocean::SetCurrentPlayList);

    return;
}

Ocean::~Ocean()
{
    qDebug() << "Destructor from Ocean.cpp";

    //Tools
    sysmanager.Free(cd);
    //widgets
    sysmanager.Free(getAddedTracksFromWidget);
    sysmanager.Free(getStringFromUserToCreateNewPlaylist);
    sysmanager.Free(getStringWithSelectedPlaylist);
    sysmanager.Free(getStringFromUserToRenamePlaylist);
    sysmanager.Free(getStringFromUserToRenameTrack);
    //UI
    sysmanager.Free(ownImage);
    sysmanager.Free(spacer);
    sysmanager.Free(ui);
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

    int short h = event->size().height();
    int short w = event->size().width();

    if((h <= 200) || (w <= 400))
        this->Hidder();
    else
        this->Shower();

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
    //Hide elements of UI
    spacer->changeSize(0, 0);
    playLists->hide();
    musicList->hide();
    nameOfTrack->hide();

    return;
}

void Ocean::Shower()
{
    //Show elements of UI
    spacer->changeSize(100, 250);
    playLists->show();
    musicList->show();
    nameOfTrack->show();

    return;
}

void Ocean::GetNamesOfSongsToMusicList(QListWidgetItem *item)
{
    //Clear list in UI
    musicList->clear();

    //Past new music list into UI
    emit this->CallOutPassNamesOfSongsToMusicList(playlistmanager->GetSongsFromCurrentPlayList(item->text()));

    return;
}

void Ocean::PassNamesOfSongsToMusicList(const QStringList &songs)
{
    QStringList buffer = songs;

    //Parsing to remove format
    for(QString &iter : buffer)
        iter = playlistmanager->ParseStringToRemoveFormatAndCurrentPath(iter);

    //Pass new tracks into music list UI
    musicList->clear();
    musicList->addItems(buffer);

    return;
}

//Drag and Drop slot
void Ocean::AddFilesAfterDropEvent(const QStringList &files)
{
    QString mp3 = ".mp3";
    QString wav = ".wav";
    QString mp4 = ".mp4";
    QStringList filesBuffer = {}; //only music files
    QStringList pathsOfFiles = {}; //finish list with paths of songs

    //----------------------------------------Parse files path
    //remove not music file
    foreach(const QString &string, files)
    {
        QString::const_iterator iter = string.end() - 1;
        QString buffer = "";

        //get format
        for(; iter != string.begin(); --iter)
        {
            //check current char
            if(*iter == ".")
            {
                //write into buffer '.' and close cycle (parsed format)
                buffer.push_front(".");
                break;
            }
            else
            {
                //write current char into buffer (and go no parsing)
                buffer.push_front(*iter);
            }
        }

        //check format of file
        if((buffer == mp3) || (buffer == wav) || (buffer == mp4))
            filesBuffer.push_front(string);
    }

    //remove pre file in begin of path
    foreach(const QString &string, filesBuffer)
    {
        QString buffer = string;

        //path of file with unicode
        buffer.remove(0, 8);
        pathsOfFiles.push_back(buffer);
    }
    //----------------------------------------Parse files path


    //----------------------------------------Add track into app or playlist (current or by name)
    //add tracks into app via copy
    importManager->SaveFileViaDragAndDrop(pathsOfFiles);

    //add tracks into current playlist (if it is not 'all' playlist)
    QListWidgetItem *item = playLists->item(playLists->currentRow());

    //return if item empty
    if(item->text() == "" || item->text() == "all")
        return;

    if(item->text() == playlistmanager->GetCurrentPlayListName())
        //add into current playlist
        emit playlistmanager->CallOutAddSongsIntoCurrentPlaylistViaDragAndDrop(importManager->GetJustAddedSongs());
    else
        //add into playlist by name
        emit playlistmanager->CallOutAddSongsIntoPlaylistByNameViaDragAndDrop(importManager->GetJustAddedSongs(), item->text());

    //show new songs
    this->GetNamesOfSongsToMusicList(item);
    //----------------------------------------Add track into app or playlist (current or by name)

    return;
}

void Ocean::SetNameOfCurrentTrackFromPlaylist(const QString &name)
{
    nameOfTrack->setText(name);

    return;
}

void Ocean::ErrorsByPlaylist(const int &error)
{
    //select error
    switch(error)
    {
        case 0: errorMessageBox->setText(errorsByPlayList.at(error)); break;
        case 1: errorMessageBox->setText(errorsByPlayList.at(error)); break;
        case 2: errorMessageBox->setText(errorsByPlayList.at(error)); break;
        case 3: errorMessageBox->setText(errorsByPlayList.at(error)); break;
        case 4: errorMessageBox->setText(errorsByPlayList.at(error)); break;
        case 5: errorMessageBox->setText(errorsByPlayList.at(error)); break;
        case 6: errorMessageBox->setText(errorsByPlayList.at(error)); break;
        default: errorMessageBox->setText("Unknown error."); break;
    }

    //show error for user
    errorMessageBox->open();

    return;
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||Slots for MainWindow||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||Slots for MainWindow||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
void Ocean::FullViaShiftF()
{
    if(this->isFullScreen())
        this->showNormal();
    else
        this->showFullScreen();

    return;
}

void Ocean::QuitViaShiftQ()
{
    QCoreApplication::quit();
}

void Ocean::HideViaShiftH()
{
    this->showMinimized();
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
    if(musicList->currentItem() == nullptr)
        return;

    QPoint globalPoint = musicList->mapToGlobal(point);

    QMenu myMenu;
    myMenu.addAction("Add to...", this, &Ocean::AddSongIntoPlayListByIndex);
    myMenu.addAction("Rename", this, &Ocean::RenameTrack);
    myMenu.addAction("Add with copy", importManager, &ImportManager::CallFileDialogOnlyCopy);
    myMenu.addAction("Add with delete", importManager, &ImportManager::CallFileDialogWithDel);
    myMenu.addAction("Delete", this, &Ocean::EraseItemFromMusicList);
    myMenu.addAction("Delete All", this, &Ocean::EraseAllItemsFromMusicList);

    myMenu.exec(globalPoint);

    return;
}

void Ocean::EraseAllItemsFromMusicList()
{
    //Clear music list inside UI
    musicList->clear();

    //Get current item of playlist
    QListWidgetItem *item = playLists->item(playLists->currentRow());

    //return if item empty
    if(item->text() == "")
        return;

    //for 'all' playlist
    if(item->text() == "all")
    {
        //Delete tracks from MAIN playlist
        emit playlistmanager->CallOutRemoveAllTracksFromPlayListByName(item->text());
        //Past new music list into UI
        emit this->CallOutPassNamesOfSongsToMusicList(playlistmanager->GetSongsFromCurrentPlayList(item->text()));
        //remove from buffer 'allSongs'
        emit playlistmanager->CallOutClearAllSongs();

        return;
    }

    //for other playlist
    if(item->text() == playlistmanager->GetCurrentPlayListName())
    {
        //Stop player if it's current playlist
        playermanager->stop();
        //And after that delete all tracks from current playlist
        emit playlistmanager->CallOutRemoveAllTracksFromCurrentPlayList();
        //Past new music list into UI
        emit this->CallOutPassNamesOfSongsToMusicList(playlistmanager->GetSongsFromCurrentPlayList(item->text()));
        //remove from buffer 'allSongs'
        emit playlistmanager->CallOutClearAllSongs();
    }
    else
    {
        //Delete tracks from other (not current) playlist
        emit playlistmanager->CallOutRemoveAllTracksFromPlayListByName(item->text());
        //Past new music list into UI
        emit this->CallOutPassNamesOfSongsToMusicList(playlistmanager->GetSongsFromCurrentPlayList(item->text()));
        //remove from buffer 'allSongs'
        emit playlistmanager->CallOutClearAllSongs();
    }

    return;
}

void Ocean::EraseItemFromMusicList()
{
    // If multiple selection is on, we need to erase all selected items
    // Get curent item on selected row
    QListWidgetItem *item = musicList->item(musicList->currentRow());

    //return if item empty
    if(item->text() == "")
        return;

    //Get name of current playlist
    QListWidgetItem *playlistIter = playLists->item(playLists->currentRow());

    //for 'all' playlist
    if(item->text() == "all")
    {
        //remove from other playlist
        emit playlistmanager->CallOutRemoveTrackFromPlayListByIndex(musicList->currentRow(), playlistIter->text());
        //Past new music list into UI
        emit this->CallOutPassNamesOfSongsToMusicList(playlistmanager->GetSongsFromCurrentPlayList(playlistIter->text()));
        //remove from buffer 'allSongs'
        emit playlistmanager->CallOutClearOneSong(musicList->currentRow());

        return;
    }

    //for other playlist
    if(playlistIter->text() == playlistmanager->GetCurrentPlayListName())
    {
        //remove from current playlist
        emit playlistmanager->CallOutRemoveTrackFromCurrentPlayListByIndex(musicList->currentRow());
        //Past new music list into UI
        emit this->CallOutPassNamesOfSongsToMusicList(playlistmanager->GetSongsFromCurrentPlayList(playlistmanager->GetCurrentPlayListName()));
        //remove from buffer 'allSongs'
        emit playlistmanager->CallOutClearOneSong(musicList->currentRow());
    }
    else
    {
        //remove from other playlist
        emit playlistmanager->CallOutRemoveTrackFromPlayListByIndex(musicList->currentRow(), playlistIter->text());
        //Past new music list into UI
        emit this->CallOutPassNamesOfSongsToMusicList(playlistmanager->GetSongsFromCurrentPlayList(playlistIter->text()));
        //remove from buffer 'allSongs'
        emit playlistmanager->CallOutClearOneSong(musicList->currentRow());
    }

    return;
}

void Ocean::AddSongIntoPlayListByIndex()
{
    getStringWithSelectedPlaylist->PassAllPlaylistsIntoWidget(GetAllItemsFromList());

    this->setDisabled(true);
    getStringWithSelectedPlaylist->show();

    return;
}

void Ocean::RenameTrack()
{
    getStringFromUserToRenameTrack->show();
    this->setDisabled(true);

    return;
}

void Ocean::RenameTrackByNewName()
{
    //Get name of current playlist (selected playlist inside UI)
    QListWidgetItem *playlist = playLists->item(playLists->currentRow());

    //Rename track
    emit playlistmanager->CallOutRenameTrackByIndex(musicList->currentRow(),//Current index of track
                                                    playlist->text(),//Pass name of playlist
                                                    getStringFromUserToRenameTrack->GetNameOfNewPlayList());//New name for track

    //close editor (to rename track) widget
    emit getStringFromUserToRenameTrack->BreakeWidget();
    //rename inside UI
    this->GetNamesOfSongsToMusicList(playlist);

    return;
}

void Ocean::ClosegetStringFromUserToRenameTrackViaCancel()
{
    this->setEnabled(true);
    getStringFromUserToRenameTrack->hide();

    return;
}

void Ocean::ParseMusicList(const QString &name)
{
    //check default playlist
    if(name == "all")
        return;

    //selected item of music list
    QListWidgetItem *trackCurrent = musicList->item(musicList->currentRow());

    //current item of playlist
    QListWidgetItem *playlistCurrent = playLists->item(playLists->currentRow());

    //Add track into playlist
    emit playlistmanager->CallOutAddSongIntoPlayList(trackCurrent->text(), //name of song
                                                     name, //selected playlist
                                                     playlistCurrent->text(), //current playlist
                                                     musicList->currentRow()); //index of song

    return;
}

void Ocean::MoveTrackUp()
{
    //Looking for current playlist
    QListWidgetItem *playlist = playLists->item(playLists->currentRow());

    //End if cureent playlist is MAIN or is empty
    if(playlist->text() == "all")
        return;

    //Looking for current track
    QListWidgetItem *currentTrack = musicList->item(musicList->currentRow());
    int currentIndex = musicList->row(currentTrack);

    //Check if current track is not exist or is first track (zero in array)
    if(currentIndex <= 0)
        return;

    //Create previuse position
    QListWidgetItem *previuseTrack = musicList->item(musicList->row(currentTrack) - 1);
    int previuseIndex = musicList->row(previuseTrack);

    //Mover item
    QListWidgetItem *temp = musicList->takeItem(previuseIndex);
    musicList->insertItem(previuseIndex, currentTrack);
    musicList->insertItem(currentIndex, temp);

    //Move track inside playlist file
    if(playlist->text() == playlistmanager->GetCurrentPlayListName())
    {
        //Move inside current playlist
        emit playlistmanager->CallOutMoveSongInsideCurrentPlayList(currentIndex, previuseIndex);


        //Find current track------------------------------------------------------
        //set current track
        playlistmanager->GetCurrentPlayList()->setCurrentIndex(previuseIndex);
        //play this track
        playermanager->play();
        //set current position
        playermanager->SetPositionOfTrack(playermanager->GetPositionOfTrack());
        //Find current track------------------------------------------------------
    }
    else
        //Move inside other playlist
        emit playlistmanager->CallOutMoveSongInsidePlayListByName(currentIndex, previuseIndex, playlist->text());

    return;
}

void Ocean::MoveTrackDown()
{
    //Move track--------------------------------------------------------------
    //Looking for current playlist
    QListWidgetItem *playlist = playLists->item(playLists->currentRow());

    //End if cureent playlist is MAIN or is empty
    if(playlist->text() == "all")
        return;

    //Looking for current track
    QListWidgetItem *currentTrack = musicList->item(musicList->currentRow());
    int currentIndex = musicList->row(currentTrack);

    //Check if current track is not exist or is last track (end of array)
    if(currentIndex == (musicList->count() - 1))
        return;

    //Create previuse position
    QListWidgetItem *nextTrack = musicList->item(musicList->row(currentTrack) + 1);
    int nextIndex = musicList->row(nextTrack);

    //Mover item
    QListWidgetItem *temp = musicList->takeItem(nextIndex);
    musicList->insertItem(nextIndex, currentTrack);
    musicList->insertItem(currentIndex, temp);

    //Move track inside playlist file
    if(playlist->text() == playlistmanager->GetCurrentPlayListName())
    {
        //Move inside current playlist
        emit playlistmanager->CallOutMoveSongInsideCurrentPlayList(currentIndex, nextIndex);

        //Find current track------------------------------------------------------
        //set current track
        playlistmanager->GetCurrentPlayList()->setCurrentIndex(nextIndex);
        //play this track
        playermanager->play();
        //set current position
        playermanager->SetPositionOfTrack(playermanager->GetPositionOfTrack());
        //Find current track------------------------------------------------------
    }
    else
        //Move inside other playlist
        emit playlistmanager->CallOutMoveSongInsidePlayListByName(currentIndex, nextIndex, playlist->text());
    //Move track--------------------------------------------------------------

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
    QPoint globalPoint = playLists->mapToGlobal(point);

    // Create menu and insert some actions
    QMenu myMenu;
    myMenu.addAction("Create", this, &Ocean::CreatePlaylist);
    myMenu.addAction("Rename", this, &Ocean::RenamePlaylist);
    myMenu.addAction("Export", this, &Ocean::ExportTrackOfPlayList);
    myMenu.addAction("Delete", this, &Ocean::EraseItemFromPlayList);

    myMenu.exec(globalPoint);

    return;
}

void Ocean::EraseItemFromPlayList()
{
    //Get current name of playlist
    QListWidgetItem *item = playLists->item(playLists->currentRow());

    //Can't delete MAIN playlist
    if(item->text() == "all")
        return;

    //If it's current playlist (clear and stop it)
    if(item->text() == playlistmanager->GetCurrentPlayListName())
    {
        //clear current playlist
        musicList->clear();
        playlistmanager->GetCurrentPlayList()->clear();
        playermanager->stop();
    }

    //Delete playlist from App
    playlistmanager->CallOutRemovePlayListByName(item->text());

    //Delete this playlist from UI
    delete item;

    return;
}

void Ocean::CreatePlaylist()
{
    this->setDisabled(true);
    getStringFromUserToCreateNewPlaylist->show();

    return;
}

void Ocean::RenamePlaylist()
{
    // Get curent item on selected row
    QListWidgetItem *item = playLists->item(playLists->currentRow());

    if((item->text() == "") || (item->text() == "all"))
        return;

    //show widget
    getStringFromUserToRenamePlaylist->show();
    this->setDisabled(true);

    return;
}

void Ocean::Rename()
{
    /*
        Rename playlist and close widget
        after user input in this method
    */

    // Get curent item on selected row
    QListWidgetItem *item = playLists->item(playLists->currentRow());

    if((item->text() == "") || (item->text() == "all"))
        return;
    else
    {
        //save index
        int index = playlistmanager->GetCurrentIndex();

        if(item->text() == playlistmanager->GetCurrentPlayListName())
        {   //For current playlist
            //rename file
            emit playlistmanager->CallOutRenameSelectedPlayList(getStringFromUserToRenamePlaylist->GetNameOfNewPlayList(), item->text());
            //rename inside UI
            item->setText(getStringFromUserToRenamePlaylist->GetNameOfNewPlayList());
            //close widget
            emit getStringFromUserToRenamePlaylist->BreakeWidget();

            //set name of playlist
            emit playlistmanager->CallOutSetCurrentPlayListName(item->text());
            //clear current playlist
            playlistmanager->GetCurrentPlayList()->clear();

            //load
            if(playlistmanager->LoadPlayList(playlistmanager->GetCurrentPlayListName()))
            {
                //load playlist
                playermanager->setPlaylist(playlistmanager->GetCurrentPlayList());
                //play playlist
                playermanager->play();
                //set current position
                playermanager->SetPositionOfTrack(playermanager->GetPositionOfTrack());

                //set track by index and play it
                playlistmanager->SetTrackByIndex(index);
            }
        }
        else //For other playlist
        {
            //rename file
            emit playlistmanager->CallOutRenameSelectedPlayList(getStringFromUserToRenamePlaylist->GetNameOfNewPlayList(), item->text());
            //rename inside UI
            item->setText(getStringFromUserToRenamePlaylist->GetNameOfNewPlayList());
            //close widget
            emit getStringFromUserToRenamePlaylist->BreakeWidget();
        }
    }

    return;
}

void Ocean::ExportTrackOfPlayList()
{
    //Get current playlist name
    QListWidgetItem *item = playLists->item(playLists->currentRow());

    //export files from playlist via ImportManager
    importManager->CallOutToExportTracksOfPlayList(item->text());

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
    emit playlistmanager->CallOutSetCurrentPlayListName(item->text());

    //clear current playlist
    playlistmanager->GetCurrentPlayList()->clear();

    //load
    if(playlistmanager->LoadPlayList(playlistmanager->GetCurrentPlayListName()))
    {
        //Set playlist and play it
        playermanager->setPlaylist(playlistmanager->GetCurrentPlayList());
        playermanager->play();
    }

    //show songs in music list
    emit this->CallOutPassNamesOfSongsToMusicList(playlistmanager->GetSongsFromCurrentPlayList(item->text()));

    return;
}

void Ocean::SetPlayListByTrack(QListWidgetItem *item)
{
    //playlist
    QListWidgetItem *iter = playLists->item(playLists->currentRow());

    if(playlistmanager->GetCurrentPlayListName() != iter->text())
    {
        //set name of playlist
        emit playlistmanager->CallOutSetCurrentPlayListName(iter->text());

        //clear current playlist
        playlistmanager->GetCurrentPlayList()->clear();

        //load playlist
        if(playlistmanager->LoadPlayList(playlistmanager->GetCurrentPlayListName()))
        {
            //Set playlist and play it
            playermanager->setPlaylist(playlistmanager->GetCurrentPlayList());
            playermanager->play();

            //set track by index and play it
            playlistmanager->SetTrackByIndex(item->listWidget()->row(item));
        }

        //show songs in music list
        emit this->CallOutPassNamesOfSongsToMusicList(playlistmanager->GetSongsFromCurrentPlayList(iter->text()));
    }
    else
    {
        //Play selected track in current playlist
        playlistmanager->SetTrackByIndex(item->listWidget()->row(item));
    }

    return;
}

void Ocean::SetCurrentPlayList()
{
    //Check current playlist with name of MAIN playlist
    if(playlistmanager->GetCurrentPlayListName() == "all")
    {
        //Save current index of track
        const unsigned short int index = playlistmanager->GetCurrentPlayList()->currentIndex();
        QString nameOfSongBuffer = "";

        //save current track name
        for(unsigned short int iter = 0; iter < musicList->count(); ++iter)
            if(iter == index)
                nameOfSongBuffer = musicList->item(index)->text();

        //clear current playlist
        playlistmanager->GetCurrentPlayList()->clear();

        //load playlist
        if(playlistmanager->LoadPlayList(playlistmanager->GetCurrentPlayListName()))
        {
            //set playlist
            playermanager->setPlaylist(playlistmanager->GetCurrentPlayList());

            //show songs in music list
            emit this->CallOutPassNamesOfSongsToMusicList(playlistmanager->GetSongsFromCurrentPlayList("all"));

            //index for set last track by index
            unsigned short int newIndex = 0;

            //find current track
            for(unsigned short int iter = 0; iter < musicList->count(); ++iter)
            {
                QString bufferOfTrackName = musicList->item(iter)->text();

                if(nameOfSongBuffer == bufferOfTrackName)
                    newIndex = iter;
            }

            //set current track
            playlistmanager->GetCurrentPlayList()->setCurrentIndex(newIndex);
            //play this track
            playermanager->play();
            //set current position
            playermanager->SetPositionOfTrack(playermanager->GetPositionOfTrack());
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
    this->setEnabled(true);
    getStringFromUserToCreateNewPlaylist->hide();

    return;
}

void Ocean::ClosegetStringFromUserToCreatePlaylist()
{
    this->setEnabled(true);
    getStringFromUserToCreateNewPlaylist->hide();

    //create widget to add tracks into new playlist
    emit this->CallOutToCreateWindowThisWidgetToGetAddedTracks();

    return;
}

void Ocean::ClosegetStringFromUserToRenameViaCancel()
{
    this->setEnabled(true);
    getStringFromUserToRenamePlaylist->hide();

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
    this->setEnabled(true);
    getStringWithSelectedPlaylist->hide();

    return;
}

void Ocean::ClosegetStringWithSelectedPlaylistViaCancel()
{
    this->setEnabled(true);
    getStringWithSelectedPlaylist->hide();

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
    //Enable main window
    this->setEnabled(true);
    //Hide own widget for add tracks into new playlist
    getAddedTracksFromWidget->hide();

    return;
}

void Ocean::PassAddedTracksIntoBuffer(const QStringList &list)
{
    //Save added track from UI to add into playlist file
    bufferOfAddedTracks.clear();
    bufferOfAddedTracks += list;

    //Add new playlist
    playLists->addItem(getStringFromUserToCreateNewPlaylist->GetNameOfNewPlayList());

    //Create new playlist
    emit playlistmanager->CallOutCreateNewPlayList(getStringFromUserToCreateNewPlaylist->GetNameOfNewPlayList(),//Name of new playlist
                                                   playlistmanager->ParseToGetFullPathOfTracks(bufferOfAddedTracks));//Added tracks for new playlist

    //Enable main window
    this->setEnabled(true);
    //Hide own widget for add tracks into new playlist
    getAddedTracksFromWidget->hide();

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
    if(getStringFromUserToCreateNewPlaylist->isHidden())
        this->setEnabled(true);
    else
        this->setDisabled(true);

    return;
}

void Ocean::IfgetStringFromUserToRenameClosed()
{
    if(getStringFromUserToRenamePlaylist->isHidden())
        this->setEnabled(true);
    else
        this->setDisabled(true);

    return;
}

void Ocean::IfgetStringWithSelectedPlaylistClosed()
{
    if(getStringWithSelectedPlaylist->isHidden())
        this->setEnabled(true);
    else
        this->setDisabled(true);

    return;
}

void Ocean::IfgetAddedTracksFromWidgetClosed()
{
    if(getAddedTracksFromWidget->isHidden())
        this->setEnabled(true);
    else
        this->setDisabled(true);

    return;
}

QStringList Ocean::GetNamesOfPlaylistsFromBinDir()
{
    cd->setCurrent(QCoreApplication::applicationDirPath() + "/bin/");
    QStringList playlists = cd->entryList(QStringList() << "*.m3u8" << "*.M3U8", QDir::Files);
    cd->setCurrent(QCoreApplication::applicationDirPath());

    return playlists;
}

void Ocean::CallWidgetAfterCreatePlaylistSlot()
{
    //Get all track from App
    QStringList buffer = playlistmanager->GetAllTracks();

    //Remove format from names of tracks
    for(QString &iter : buffer)
        iter = playlistmanager->ParseStringToRemoveFormatAndCurrentPath(iter);

    //Pass all tracks from main window into widget
    getAddedTracksFromWidget->GetAllSongsfFromMainWindow(buffer);

    //Disable main window
    this->setDisabled(true);
    //Show own widget for add tracks into new playlist
    getAddedTracksFromWidget->show();

    return;
}

void Ocean::WriteDefaultPlayList()
{
    //Check first elemet there is playlists to find MAIN playlist
    if(playLists->item(0)->text() == "all")
        return;
    else//Write into UI MAIN playlist
        playLists->addItem("all");

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
    //List with names of playlist
    QStringList buffer;

    //Get all names of playlist from UI
    for(unsigned short int iter = 0; iter < playLists->count(); ++iter)
    {
        QListWidgetItem* item = playLists->item(iter);
        buffer.push_back(item->text());
    }

    return  buffer;
}

/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||METHODS FOR UI||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
