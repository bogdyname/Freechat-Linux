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
    file->QFile::open(QFile::ReadOnly);
    app.QApplication::setStyleSheet(file->QFile::readAll());

    Ocean window;

    window.QWidget::show();

    return app.QApplication::exec();
}
