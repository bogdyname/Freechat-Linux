/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#ifndef SLIDER_H
#define SLIDER_H

#include <QWidget>
#include <QSlider>
#include <QDebug>
#include <QString>

using namespace Qt;

class Slider : public QSlider
{
    Q_OBJECT

public:
    Slider(QWidget *parent = nullptr, int position = 0);
};

#endif // SLIDER_H
