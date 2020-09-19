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

    Button::switchIcon = nullptr;

    connect(this, &QAbstractButton::pressed, this, &Button::buttonPressed);
    connect(this, &QAbstractButton::released, this, &Button::buttonReleased);

    delete icon;
    return;
}

Button::~Button()
{
    delete switchIcon;

    return;
}

void Button::SetIconForSwitch(QString item)
{
    this->switchIcon = new QString(item);
}

void Button::buttonPressed()
{
    /*QIcon *icon = new QIcon("://images/" + this->objectName() + "_pressed.png");
    this->setIcon(*icon);

    delete icon;
    return;*/

   /* QIcon *icon;

    switch(*this->switchCounter)
    {
        //Play current track
        case 0:
        {
            icon = new QIcon("://images/" + *this->switchIcon + "_pressed.png");
            this->setIcon(*icon);
        }
        break;

        //Pause current track
        case 1:
        {
            icon = new QIcon("://images/" + this->objectName() + "_pressed.png");
            this->setIcon(*icon);
        }
        break;
    }

    delete icon;
    return;*/

    QIcon *icon;
    static int counter = 1;

    counter == 1 ? --counter : ++counter ;

    switch(counter)
    {
        //Play current track
        case 0:
        {
            icon = new QIcon("://images/" + this->objectName() + "_pressed.png");
            this->setIcon(*icon);
        }
        break;

        //Pause current track
        case 1:
        {
            icon = new QIcon("://images/" + *this->switchIcon + "_pressed.png");
            this->setIcon(*icon);
        }
        break;
    }

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

void Button::changeIcon(int &counter)
{
    QIcon *icon;

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

    delete icon;
    return;
}
