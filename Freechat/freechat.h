/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef FREECHAT_H
#define FREECHAT_H

#include "ui_freechat.h"
#include "datasave.h"
#include <QTextTableFormat>
#include <QTextEdit>
#include <QDialog>

class Freechat : public QDialog, private Ui::Freechat
{
    Q_OBJECT

public:
    Freechat(QWidget *parent = nullptr);
};

#endif // FREECHAT_H
