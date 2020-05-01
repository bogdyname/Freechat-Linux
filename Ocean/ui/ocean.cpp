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
        Ocean::listMusic = new QListWidget();
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

    Ocean::ui->horizontalLayout->QHBoxLayout::addWidget(Ocean::listMusic);

    //TTS
    Ocean::ui->horizontalLayout->QHBoxLayout::addWidget(Ocean::buttonForAddMusicWithDel);
    Ocean::ui->horizontalLayout->QHBoxLayout::addWidget(Ocean::buttonForAddMusicOnlyCopy);
    //TTS

    //STYLE
    Ocean::listMusic->QWidget::setMaximumWidth(150);
    Ocean::listMusic->QWidget::setMinimumWidth(150);

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
    delete Ocean::listMusic;
    delete Ocean::buttonForAddMusicWithDel;
    delete Ocean::buttonForAddMusicOnlyCopy;

    //Own classes
    delete Ocean::importManager;
}
