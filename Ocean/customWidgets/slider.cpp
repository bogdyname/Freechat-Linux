/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#include "slider.h"

Slider::Slider(QWidget *parent, int position)
    : QSlider(parent)
{
    this->setOrientation(Qt::Horizontal);
    this->QAbstractSlider::setSliderPosition(position);

    return;
}
