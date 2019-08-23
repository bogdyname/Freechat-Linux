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
                                 tr("Your IP address: "), yourIp);
        break;
    case false:
        break;
    }

    return;
}
