/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include <QtWidgets>
#include "Bin/freechat.h"
#include "Network/connectionf2f.h"

using namespace Qt;

Freechat::Freechat(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    lineForTypeText->setFocusPolicy(StrongFocus);
    textFieldForViewMessages->setFocusPolicy(NoFocus);
    textFieldForViewMessages->setReadOnly(true);
    listWithIpOfUsers->setFocusPolicy(NoFocus);

    connect(&showNetworkInfo, SIGNAL(), SLOT());

}

void Freechat::on_showNetworkSettings_clicked(bool checked)
{
        QString text = QInputDialog::getText(this, tr("Network settings"),
        tr("Write IP address of peer:"),
        QLineEdit::Normal, QDir::home().dirName(), &checked);

        if (checked && !text.isEmpty())
        {
            writeIpOfPeer->setText(text);
        }
        else
        {
            /*clear code*/
        }

        return;
}

void Freechat::on_showNetworkInfo_clicked(bool checked)
{

}
