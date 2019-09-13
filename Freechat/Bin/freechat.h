/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef FREECHAT_H
#define FREECHAT_H

#include "Bin/bin.h"
#include "ui_freechat.h"
#include <QTextTableFormat>
#include <QMessageBox>
#include <QtWidgets>
#include <QDialog>

using namespace Qt;

class Freechat : public QDialog, private Ui::Freechat
{
    Q_OBJECT

private:
    static QString lanIpOfPeer;
    static QString wanIpOfPeer;
    static QString nickNameOfPeer;
    static QString yourIp;
    bool *replyForCD = nullptr; //not sure

public:
    Freechat(QWidget *parent = nullptr);
    ~Freechat();

private:
    void AskForConnectingToPortPeer();
    void AskForDisconnectingFromPortPeer();
    bool ReplyFromPortPeer(bool &reply);

signals:
    void SetTextInsideFiledOfChat();

private slots:
    void on_showNetworkInfo_clicked(bool checked);
    void on_connectionToPeer_clicked(bool checked);

    void on_writeNickOfPeer_textChanged();
    void on_writeLanIpOfPeer_textChanged();
    void on_writeWanIpOfPeer_textChanged();
    void on_wanButton_clicked(bool checked);
    void on_lanButton_clicked(bool checked);
    void on_nickButton_clicked(bool checked);

    void on_listWithIpOfUsers_itemDoubleClicked(QListWidgetItem *item);

    void on_lineForTypeText_textEdited(const QString &arg1);

private:
    Ui::Freechat *ui;
};
#endif
