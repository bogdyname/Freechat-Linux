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
    icon = new QIcon("://images/" + this->objectName() + ".png");
    this->setIcon(*icon);

    Button::switchIcon = nullptr;

    connect(this, &QAbstractButton::pressed, this, &Button::buttonPressed);
    connect(this, &QAbstractButton::released, this, &Button::buttonReleased);

    return;
}

Button::~Button()
{
    delete switchIcon;
    delete icon;

    return;
}

void Button::SetIconForSwitch(QString item)
{
    this->switchIcon = new QString(item);
}

void Button::buttonPressed()
{
    icon = new QIcon("://images/" + this->objectName() + "_pressed.png");
    this->setIcon(*icon);

    return;
}

void Button::buttonReleased()
{
    icon = new QIcon("://images/" + this->objectName() + ".png");
    this->setIcon(*icon);

    return;
}

void Button::changeIcon(const int &counter)
{
    switch(counter)
    {
        //Play current track
        case 0:
        {
            icon = new QIcon("://images/" + this->objectName() + ".png");
            this->setIcon(*icon);
        }
        break;

        //Pause current track
        case 1:
        {
            icon = new QIcon("://images/" + *this->switchIcon + ".png");
            this->setIcon(*icon);
        }
        break;
    }

    return;
}
