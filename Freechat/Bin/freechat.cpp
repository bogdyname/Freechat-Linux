/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Bin/freechat.h"
#include "Network/connectionf2f.h"

Freechat::Freechat(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    lineForTypeText->setFocusPolicy(StrongFocus);
    textFieldForViewMessages->setFocusPolicy(NoFocus);
    textFieldForViewMessages->setReadOnly(true);
    listWithIpOfUsers->setFocusPolicy(NoFocus);

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

        AskForConnectingToPortPeer(); //ask for connection

        if(ReplyFromPortPeer(reply) == true) // reply
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
