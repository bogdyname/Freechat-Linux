#include "ui/ocean.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile *file = new QFile(":/style.css");
    file->QIODevice::open(QFile::ReadOnly);
    a.QApplication::setStyleSheet(file->QIODevice::readAll());

    Ocean window;

    window.QWidget::show();

    return a.QApplication::exec();
}
