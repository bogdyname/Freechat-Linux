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
        Ocean::spacer = new QSpacerItem(100, 250);
        Ocean::ownImage = new QPixmap();
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

        //Tools for widgets
        Ocean::timerForCheckWidgetOfCreatPlayList = new QTimer();

        //Object of own classes
        Ocean::getStringFromUser = new GetStringWidget();
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
    Ocean::ui->tool->QVBoxLayout::addItem(Ocean::spacer);
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

    //Slider of track
    Ocean::sliderOfTrack->QWidget::setMinimumWidth(225);




    //TTS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if(Ocean::ownImage->QPixmap::load("/root/29614_original.jpg", "jpg", Qt::AutoColor))
        qDebug() << "true";
    else
        qDebug() << "false";

    //Ocean::ownImage->QPixmap::scaled(150, 150, Qt::IgnoreAspectRatio, Qt::FastTransformation);
    const QPixmap *imageTTS = Ocean::ownImage;
    //TTS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!




    //Image of playlist
    Ocean::imageOfPlayList->QLabel::setPixmap(*imageTTS);
    Ocean::imageOfPlayList->QWidget::setMinimumSize(200, 150);
    Ocean::imageOfPlayList->QWidget::setMaximumSize(225, 200);

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

    /*--------------------------------------------------TOOLS--------------------------------------------------*/
    //Timer for check widget of create playlist
    Ocean::timerForCheckWidgetOfCreatPlayList->QTimer::setInterval(500);
    Ocean::timerForCheckWidgetOfCreatPlayList->QTimer::start();

    /*--------------------------------------------------TOOLS--------------------------------------------------*/


    /*
        *****!CONNECT SIGNALS WITH SLOTS!*****

    ---------------------Managers---------------------
    1)Import manager connect
        1.1) Add new music and delete it via button
        1.2) Add new music (only copy) via button
    2)Player manager
        2.1) play track
        2.2) stop track
        2.3) set current playlist via playlist manager (emited signal from SLOT(SetPlayList(QListWidgetItem *)))
    3)Playlist manager
        3.1) next track
        3.2) previous track
    ---------------------Managers---------------------

    -----------------------UI-------------------------
    4)UI lists widgets
        4.1) set playlist then item clicked (UI only)
        4.2) Context Menu for playlist
        4.3) Context Menu for music list
        4.4) show songs in music list
    5)Widget of create playlist
        5.1) close widget of create playlist via cancel button
        5.2) close widget of create playlist via okay button and pass QString into slot
    -----------------------UI-------------------------

    ----------------------Tools-----------------------
    6)Timer for check CreateListWidget
        6.1) check widget of create playlist (UI --> 5) to close it if pressed keys Alt+F4
    ----------------------Tools-----------------------
    */

    //Managers-----------------------------------------
    //Import manager
    QObject::connect(Ocean::buttonForAddMusicWithDel, SIGNAL(clicked(bool)), Ocean::importManager, SLOT(CallFileDialogWithDel()));
    QObject::connect(Ocean::buttonForAddMusicOnlyCopy, SIGNAL(clicked(bool)), Ocean::importManager, SLOT(CallFileDialogOnlyCopy()));
    //Player manager
    QObject::connect(Ocean::playTrack, &QPushButton::clicked, Ocean::playermanager, &QMediaPlayer::play);
    QObject::connect(Ocean::stopTrack, &QPushButton::clicked, Ocean::playermanager, &QMediaPlayer::stop);
    QObject::connect(Ocean::playlistmanager, &Playlist::SetDefaultPlayList, Ocean::playermanager, &QMediaPlayer::setPlaylist);
    QObject::connect(Ocean::playlistmanager, &Playlist::SetCurrentPlayList, Ocean::playermanager, &QMediaPlayer::setPlaylist);
    //Playlist manager
    QObject::connect(Ocean::nextTrack, &QPushButton::clicked, Ocean::playlistmanager, &QMediaPlaylist::next);
    QObject::connect(Ocean::previousTrack, &QPushButton::clicked, Ocean::playlistmanager, &QMediaPlaylist::previous);

    //UI-----------------------------------------------
    //UI Lists
    QObject::connect(Ocean::playLists, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(GetNamesOfSongsToMusicList(QListWidgetItem *)));
    QObject::connect(Ocean::playLists, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(SetPlayList(QListWidgetItem *)));
    QObject::connect(Ocean::playLists, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(ShowContextMenuOfPlayList(QPoint)));
    QObject::connect(Ocean::musicList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(ShowContextMenuOfMusicList(QPoint)));
    QObject::connect(this, &Ocean::CallOutPassNamesOfSongsToMusicList, this, &Ocean::PassNamesOfSongsToMusicList);
    //Widget for get string from user
    QObject::connect(Ocean::getStringFromUser, &GetStringWidget::BreakeWidget, this, &Ocean::CloseWidgetForGetStringViaCancel);
    QObject::connect(Ocean::getStringFromUser, &GetStringWidget::SendName, this, &Ocean::CloseWidgetForGetStringViaOkay);

    //Tools--------------------------------------------
    //Timer for check widget of create playlist
    QObject::connect(Ocean::timerForCheckWidgetOfCreatPlayList, &QTimer::timeout, this, &Ocean::IfCreateListWidgetClosed);

    return;
}

Ocean::~Ocean()
{
    //UI
    delete Ocean::ownImage;
    delete Ocean::spacer;
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

    //Tools
    delete Ocean::timerForCheckWidgetOfCreatPlayList;

    //Own classes
    delete Ocean::importManager;
    delete Ocean::playlistmanager;
    delete Ocean::playermanager;
    delete Ocean::getStringFromUser;

    return;
}

void Ocean::Hidder()
{
    Ocean::spacer->QSpacerItem::changeSize(0, 0);
    Ocean::playLists->QWidget::hide();
    Ocean::musicList->QWidget::hide();
    Ocean::sortBy->QWidget::hide();
    Ocean::buttonForAddMusicWithDel->QWidget::hide();
    Ocean::buttonForAddMusicOnlyCopy->QWidget::hide();

    return;
}

void Ocean::Shower()
{
    Ocean::spacer->QSpacerItem::changeSize(100, 250);
    Ocean::playLists->QWidget::show();
    Ocean::musicList->QWidget::show();
    Ocean::sortBy->QWidget::show();
    Ocean::buttonForAddMusicWithDel->QWidget::show();
    Ocean::buttonForAddMusicOnlyCopy->QWidget::show();

    return;
}

void Ocean::GetNamesOfSongsToMusicList(QListWidgetItem *item)
{
    if(item->QListWidgetItem::text() == "all")
        emit CallOutPassNamesOfSongsToMusicList(Ocean::playlistmanager->Playlist::GetSongsFromDeaultPlayList());
    else
        emit CallOutPassNamesOfSongsToMusicList(Ocean::playlistmanager->Playlist::GetSongsFromCurrentPlayList(item->QListWidgetItem::text()));

    return;
}

void Ocean::PassNamesOfSongsToMusicList(const QStringList &songs)
{
    Ocean::musicList->QListWidget::addItems(songs);

    return;
}

void Ocean::ShowContextMenuOfPlayList(const QPoint &point)
{
    QPoint globalPoint = Ocean::playLists->QWidget::mapToGlobal(point);

    // Create menu and insert some actions
    QMenu myMenu;
    myMenu.QMenu::addAction("Save", this, SLOT(SavePlaylist()));
    myMenu.QMenu::addAction("Rename", this, SLOT(RenamePlaylist()));
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
    myMenu.QMenu::addAction("Delete All", this, SLOT(EraseAllItemsFromMusicList()));

    myMenu.QMenu::exec(globalPoint);

    //write here method from importmanager.h

    return;
}

void Ocean::EraseAllItemsFromMusicList()
{
    //TTS
    Ocean::musicList->QListWidget::clear();
    //TTS

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
    Ocean::getStringFromUser->QWidget::show();

    return;
}

void Ocean::RenamePlaylist()
{
    for(unsigned short int iter = 0; iter < Ocean::playLists->QListWidget::selectedItems().size(); ++iter)
    {
        // Get curent item on selected row
        QListWidgetItem *item = Ocean::playLists->QListWidget::item(Ocean::playLists->QListWidget::currentRow());

        qDebug() << item->text();

        //need to call here ui 'createplaylisywidget' for get string with newName of playlist
        //then emit signal

        if((item->text() == "") || (item->text() == "all"))
            return;
        //else
            //emit Ocean::playlistmanager->Playlist::CallOutRenameSelectedPlayList();
    }

    return;
}

void Ocean::SavePlaylist()
{
    for(unsigned short int iter = 0; iter < Ocean::playLists->QListWidget::selectedItems().size(); ++iter)
    {
        // Get curent item on selected row
        QListWidgetItem *item = Ocean::playLists->QListWidget::item(Ocean::playLists->QListWidget::currentRow());

        qDebug() << item->text();

        //create if() for QMediaPlaylist (currentPlaylist || other playlist)
    }

    return;
}

void Ocean::SetPlayList(QListWidgetItem *item)
{
    if(item->QListWidgetItem::text() == "all")
    {
        Ocean::playlistmanager->Playlist::LoadDefaultPlayList();
        emit Ocean::playlistmanager->Playlist::SetDefaultPlayList(Ocean::playlistmanager->Playlist::GetDefaultPlayList());
        emit Ocean::playlistmanager->Playlist::CallOutSetCurrentPlayListName("all");
        //show songs in music list
        emit CallOutPassNamesOfSongsToMusicList(Ocean::playlistmanager->Playlist::GetSongsFromDeaultPlayList());
    }
    else
    {
        //set name of playlist
        emit Ocean::playlistmanager->Playlist::CallOutSetCurrentPlayListName(item->QListWidgetItem::text());

        Ocean::playlistmanager->Playlist::LoadPlayList(Ocean::playlistmanager->Playlist::GetCurrentPlayListName());

        //Emit signal from Playlist.h with current playlist
        emit Ocean::playlistmanager->Playlist::SetCurrentPlayList(Ocean::playlistmanager->Playlist::GetCurrentPlayList());
        //show songs in music list
        emit CallOutPassNamesOfSongsToMusicList(Ocean::playlistmanager->Playlist::GetSongsFromCurrentPlayList(item->QListWidgetItem::text()));
    }

    return;
}

void Ocean::CloseWidgetForGetStringViaCancel()
{
    this->QWidget::setEnabled(true);
    Ocean::getStringFromUser->QWidget::hide();

    return;
}

void Ocean::CloseWidgetForGetStringViaOkay(const QString &name)
{
    //before delete widget need to pass data into playlist

    this->QWidget::setEnabled(true);
    Ocean::playLists->QListWidget::addItem(name);
    Ocean::getStringFromUser->QWidget::hide();

    return;
}

void Ocean::IfCreateListWidgetClosed()
{
    if(Ocean::getStringFromUser->QWidget::isHidden())
        this->QWidget::setEnabled(true);
    else
        this->QWidget::setDisabled(true);

    return;
}

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
