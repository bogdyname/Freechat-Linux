/*
***Copyright (C) 2019 Softwater Inc
***Contact: bogdyname@gmail.com
*/

#ifndef FREECHAT_H
#define FREECHAT_H

#include "ui_freechat.h"
#include "userclient.h"
#include <QTextTableFormat>
#include <QDialog>

class Freechat : public QDialog, private Ui::Freechat
{
    Q_OBJECT

public:
    Freechat(QWidget *parent = nullptr);

public slots:
    void appendMessage(const QString &from, const QString &message);

private slots:
    void returnPressed();
    void hiiiiiiBoy();
    void userIsJoined(const QString &nick);
    void userIsLeft(const QString &nick);

private:
    UserClient userclient;
    QString whoami;
    QTextTableFormat tableFormat;
};

#endif // FREECHAT_H
