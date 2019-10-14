/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Bin/bin.h"
#include "Bin/freechat.h"
#include "Network/connectionf2f.h"

 QString Freechat::globalBuffer;
 QString Freechat::viewField;
 QString Freechat::yourIp;
 QString Freechat::lanIpOfPeer;
 QString Freechat::wanIpOfPeer;
 QString Freechat::nickNameOfPeer;
 QString Freechat::bufferOfMessages;

Freechat::Freechat(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::Freechat)
{
    ui->setupUi(this);


    ui->lineForTypeText->setFocusPolicy(StrongFocus);
    ui->textFieldForViewMessages->setFocusPolicy(NoFocus);
    ui->textFieldForViewMessages->setReadOnly(true);
    ui->listWithNickName->setFocusPolicy(NoFocus);

    //connect(lineForTypeText, SIGNAL(returnPressed()), this, SLOT(clear()));

}

Freechat::~Freechat()
{
    delete ui;
}

void Freechat::on_showNetworkInfo_clicked(bool checked)
{
    switch(checked)
    {
    case true:
        QMessageBox::information(this, tr("Network Info"),
                                 tr("Your LAN IP address: "), yourIp);
        break;
    case false:
        QMessageBox::information(this, tr("Error"),
                                 tr("Check your network connection."));
        break;
    }

    return;
}

void Freechat::on_connectionToPeer_clicked(bool checked)
{
    switch(checked)
    {
    case true:
    {
        QMessageBox::information(this, tr("Connection"),
                                 tr("Connecting to peer..."));
    }
        break;
    case false:
        QMessageBox::information(this, tr("Disconnected"),
                                 tr("Peer does not want to connect with you"));
        break;
    }

    return;
}

/*
void Freechat::on_lineForTypeText_textEdited(QString &messages)
{
    messages = ui->lineForTypeText->text(); //pass text from line for type
    bufferOfMessages += messages;//write inside buffer

    return;
}
*/
