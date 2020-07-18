/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#include "ui/ocean.h"
#include <QApplication>
#include <QTextCodec>
#include <QFile>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));

    QApplication app(argc, argv);

    QFile *file = new QFile(":/style.css");

    if(file->open(QFile::ReadOnly))
        app.setStyleSheet(file->readAll());

    Ocean window;

    window.QWidget::show();

    return app.QApplication::exec();
}
