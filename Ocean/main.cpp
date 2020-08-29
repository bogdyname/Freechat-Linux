/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#include <QApplication>
#include <QThread>
#include <QFile>

//own classes
#include "network/networkmanager.h"
#include "ui/ocean.h"

//check alloc memory in system

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //Default style of app
    QFile *file = new QFile(":/vampire_theme.css");

    if(file->open(QFile::ReadOnly))
        app.setStyleSheet(file->readAll());

    //MainWindow (all UI)
    Ocean window;
    window.show();

    return app.QApplication::exec();
}
