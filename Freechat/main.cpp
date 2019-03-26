/*
***Copyright (C) 2019 Softwater Inc
***Contact: bogdyname@gmail.com
*/

#include "freechat.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Freechat w;
    w.show();

    return a.exec();
}
