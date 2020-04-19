#include "ui/worldcash.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WorldCash window;

    window.QWidget::setMinimumWidth(575);
    window.QWidget::setMinimumHeight(500);

    window.QWidget::show();

    return a.QApplication::exec();
}
