/*
***Copyright (C) 2019 Freechat Inc
***Contact: bogdyname@gmail.com
*/

#ifndef FREECHAT_H
#define FREECHAT_H

#include <QMainWindow>

namespace Ui {
class Freechat;
}

class Freechat : public QMainWindow
{
    Q_OBJECT

public:
    explicit Freechat(QWidget *parent = nullptr);
    ~Freechat();

private:
    Ui::Freechat *ui;
};

#endif // FREECHAT_H
