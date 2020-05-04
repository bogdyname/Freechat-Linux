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

    try
    {
        //Objects of UI
        Ocean::imageOfPlayList = new QLabel();
        Ocean::sortBy = new QComboBox();
        Ocean::sliderOfTrack = new QSlider(Qt::Horizontal);
        Ocean::playLists = new QListWidget();
        Ocean::musicList = new QListWidget();
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

    //UpSide
    //Player
    Ocean::ui->buttonsOfPlayer->QHBoxLayout::addWidget(Ocean::stopTrack);
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
    //Tool buttons
    Ocean::ui->tool->QVBoxLayout::addWidget(Ocean::buttonForAddMusicWithDel);
    Ocean::ui->tool->QVBoxLayout::addWidget(Ocean::buttonForAddMusicOnlyCopy);
    Ocean::ui->tool->QVBoxLayout::addWidget(Ocean::sortBy);

    //Main window
    this->QWidget::setMinimumSize(250, 300);

    //Lists
    Ocean::playLists->QWidget::setMaximumWidth(225);
    Ocean::musicList->QWidget::setMaximumWidth(1500);

    //Sort box
    Ocean::sortBy->QComboBox::addItem("Name");
    Ocean::sortBy->QComboBox::addItem("Date");

    //Buttons for open file
    Ocean::buttonForAddMusicWithDel->QPushButton::setText("Add music with delete");
    Ocean::buttonForAddMusicOnlyCopy->QPushButton::setText("Add music with copy");

    //Buttons for player
    Ocean::stopTrack->QPushButton::setText("Stop");
    Ocean::playTrack->QPushButton::setText("Play");
    Ocean::nextTrack->QPushButton::setText("Next");

    /*
        *!CONNECT SIGNALS WITH SLOTS!*
    Import manager connect
        1) Add new music and delete it via button
        2) Add new music (only copy) via button
    */
    //Import manager
    QObject::connect(Ocean::buttonForAddMusicWithDel, SIGNAL(clicked(bool)), Ocean::importManager, SLOT(CallFileDialogWithDel()));
    QObject::connect(Ocean::buttonForAddMusicOnlyCopy, SIGNAL(clicked(bool)), Ocean::importManager, SLOT(CallFileDialogOnlyCopy()));

    //Main window style
    QObject::connect(this, SIGNAL(iconSizeChanged(QSize)), this, SLOT(Hidder(QSize)));

    return;
}

Ocean::~Ocean()
{
    //UI
    delete Ocean::ui;
    delete Ocean::imageOfPlayList;
    delete Ocean::sortBy;
    delete Ocean::sliderOfTrack;
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

    return;
}

void Ocean::WindowhasNewSize(QResizeEvent *event)
{
    //QSize size = event->oldSize();

    return;
}

void Ocean::Hidder(const QSize &size)
{
    QSize min(300, 300);

    if(size == min)
        Ocean::playLists->hide();

    return;
}

void Ocean::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    emit WindowhasNewSize(event);

    return;
}
