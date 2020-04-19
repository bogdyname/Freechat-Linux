#include "ui/worldcash.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WorldCash window;

    window.QWidget::setMinimumWidth(400);
    window.QWidget::setMinimumHeight(400);

    window.QWidget::show();

    return a.QApplication::exec();
}
