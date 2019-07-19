/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef FREECHAT_H
#define FREECHAT_H

#include "Bin/bin.h"
#include "ui_freechat.h"
#include <QTextTableFormat>
#include <QDialog>

using namespace Qt;

class Freechat : public QDialog, private Ui::Freechat
{
    Q_OBJECT

private:
    QString IpOfPeer;
    QString NickNameOfPeer;

public:
    Freechat(QWidget *parent = nullptr);
    ~Freechat();

private slots:
    void on_showNetworkSettings_clicked(bool checked);
    void on_showNetworkInfo_clicked(bool checked);
    void on_writeIpOfPeer_textEdited(const QString &arg1);
    void on_writeNickOfPeer_textEdited(const QString &arg1);
};
#endif
