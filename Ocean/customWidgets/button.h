/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#ifndef BUTTON_H
#define BUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QIcon>
#include <QString>
#include <QDebug>

class Button : public QPushButton
{
    Q_OBJECT

public:
    Button(QWidget *parent = nullptr, QString iconName = " ");
};

#endif // BUTTON_H
