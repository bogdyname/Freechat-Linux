/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#include "button.h"

Button::Button(QWidget *parent, QString objName)
    :  QPushButton(parent)
{
    this->setObjectName(objName);
    QIcon *icon = new QIcon("://images/" + this->objectName() + ".png");
    this->setIcon(*icon);

    connect(this, &QAbstractButton::pressed, this, &Button::buttonPressed);
    connect(this, &QAbstractButton::released, this, &Button::buttonReleased);

    delete icon;
    return;
}

void Button::buttonPressed()
{
    QIcon *icon = new QIcon("://images/" + this->objectName() + "_pressed.png");
    this->setIcon(*icon);

    delete icon;
    return;
}

void Button::buttonReleased()
{
    QIcon *icon = new QIcon("://images/" + this->objectName() + ".png");
    this->setIcon(*icon);

    delete icon;
    return;
}
