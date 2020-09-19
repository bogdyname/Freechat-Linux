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

private:
    QString *switchIcon;

public:
    Button(QWidget *parent = nullptr, QString objName = " ");
    ~Button();
    void SetIconForSwitch(QString item);

public slots:
    void buttonPressed();
    void buttonReleased();
    void changeIcon(int &counter);

};

#endif // BUTTON_H
