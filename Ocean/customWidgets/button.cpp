/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#include "button.h"

Button::Button(QWidget *parent, QString iconName)
    :  QPushButton(parent)
{
    QIcon *icon = new QIcon(iconName);
    this->setIcon(*icon);

    delete icon;
    return;
}
