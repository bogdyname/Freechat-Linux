/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#include "ui/ocean.h"
#include <QFileDialog>

Ocean::Ocean(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Ocean)
{
    Ocean::ui->setupUi(this);

    try
    {
        //Objects of UI
        Ocean::imageOfPlayList = new QLabel();
        Ocean::sortBy = new QComboBox();
        Ocean::playLists = new QListWidget();
        Ocean::musicList = new QListWidget();
        Ocean::mediaPlayer = new QMediaPlayer();
        Ocean::mediaPlayList = new QMediaPlaylist();
        Ocean::playTrack = new QPushButton();
        Ocean::stopTrack = new QPushButton();
        Ocean::nextTrack = new QPushButton();
        Ocean::previousTrack = new QPushButton();
        Ocean::buttonForAddMusicWithDel = new QPushButton();
        Ocean::buttonForAddMusicOnlyCopy = new QPushButton();

        //Object of own classes
        Ocean::importManager = new ImportManager();
    }
    catch (std::bad_alloc &exp)
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

    Ocean::ui->horizontalLayout->QHBoxLayout::addWidget(Ocean::playLists);
    Ocean::ui->horizontalLayout->QHBoxLayout::addWidget(Ocean::musicList);

    Ocean::ui->toolLayout->QVBoxLayout::addWidget(Ocean::imageOfPlayList);
    Ocean::ui->toolLayout->QVBoxLayout::addWidget(Ocean::sortBy);
    Ocean::ui->toolLayout->QVBoxLayout::addWidget(Ocean::buttonForAddMusicWithDel);
    Ocean::ui->toolLayout->QVBoxLayout::addWidget(Ocean::buttonForAddMusicOnlyCopy);

    //STYLE

    //Main window
    this->QWidget::setMinimumSize(250, 300);

    //Image of play list
    Ocean::imageOfPlayList->QWidget::setMinimumSize(200, 250);
    Ocean::imageOfPlayList->QWidget::setMaximumSize(350, 400);

    //Music list
    Ocean::musicList->QWidget::setMaximumWidth(150);
    Ocean::musicList->QWidget::setMinimumWidth(150);
    Ocean::musicList->QWidget::setMinimumHeight(150);

    //Play list
    Ocean::playLists->QWidget::setMaximumWidth(150);
    Ocean::playLists->QWidget::setMinimumWidth(150);
    Ocean::playLists->QWidget::setMinimumHeight(150);

    /*
        *!CONNECT SIGNALS WITH SLOTS!*
    Import manager connect
        1) Add new music and delete it via button
        2) Add new music (only copy) via button
    */
    //Import manager
    QObject::connect(Ocean::buttonForAddMusicWithDel, SIGNAL(clicked(bool)), Ocean::importManager, SLOT(CallFileDialogWithDel()));
    QObject::connect(Ocean::buttonForAddMusicOnlyCopy, SIGNAL(clicked(bool)), Ocean::importManager, SLOT(CallFileDialogOnlyCopy()));
}

Ocean::~Ocean()
{
    //UI
    delete Ocean::ui;
    delete Ocean::imageOfPlayList;
    delete Ocean::sortBy;
    delete Ocean::playLists;
    delete Ocean::musicList;
    delete Ocean::mediaPlayer;
    delete Ocean::mediaPlayList;
    delete Ocean::playTrack;
    delete Ocean::stopTrack;
    delete Ocean::nextTrack;
    delete Ocean::previousTrack;
    delete Ocean::buttonForAddMusicWithDel;
    delete Ocean::buttonForAddMusicOnlyCopy;

    //Own classes
    delete Ocean::importManager;
}
