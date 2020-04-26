#include "ui/worldcash.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile *file = new QFile(":/style.css");
    file->QIODevice::open(QFile::ReadOnly);
    a.QApplication::setStyleSheet(file->QIODevice::readAll());

    Ocean window;

    window.QWidget::setMinimumWidth(575);
    window.QWidget::setMinimumHeight(500);

    window.QWidget::show();

    return a.QApplication::exec();
}
