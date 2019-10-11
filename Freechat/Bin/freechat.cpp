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
        break;
    }

    return;
}

void Freechat::on_connectionToPeer_clicked(bool checked)
{
    bool reply = false;

    switch(checked)
    {
    case true:
    {
        QMessageBox::information(this, tr("Connection"),
                                 tr("Connecting to peer..."));

        AskForConnectingToPortPeer();

        if(ReplyFromPortPeer(reply) == true)
        {

        }
        else
        {
            QMessageBox::information(this, tr("Disconnected"),
                                     tr("Peer does not want to connect with you"));
        }
    }
        break;
    case false:
        break;
    }

    return;
}

void Freechat::AskForConnectingToPortPeer()
{

    return;
}

void Freechat::AskForDisconnectingFromPortPeer()
{

    return;
}

bool Freechat::ReplyFromPortPeer(bool &reply)
{
    if(reply == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Freechat::on_writeNickOfPeer_textChanged()
{

    return;
}
void Freechat::on_writeLanIpOfPeer_textChanged()
{

    return;
}

void Freechat::on_writeWanIpOfPeer_textChanged()
{


    return;
}

void on_listWithNickName_itemDoubleClicked(QListWidgetItem *item)
{

}

void Freechat::on_lineForTypeText_textEdited(QString &messages)
{
    connect(lineForTypeText, SIGNAL(inputRejected()), this, SLOT(PassMessagesInsideBuffer()));
    connect(lineForTypeText, SIGNAL(returnPressed()), this, SLOT(SlotSendToServer()));

    messages = ui->lineForTypeText->text(); //pass text from line for type
    bufferOfMessages += messages;//write inside buffer

    return;
}
