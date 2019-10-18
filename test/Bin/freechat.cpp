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

    //Network check connection
    /*
    QNetworkAccessManager nam;
    QNetworkRequest req(QUrl("http://www.google.com"));
    QNetworkReply *reply = nam.get(req);
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if(reply->bytesAvailable())
    {
        ui->writeNickOfPeer->setReadOnly(true);
        ui->writeWanIpOfPeer->setReadOnly(true);
        ui->writeLanIpOfPeer->setReadOnly(true);
        ui->lineForTypeText->setReadOnly(true);
    }
    else
    {
        /*clear code
    }
    */

    //Network
    Peerout peer;
    Peerin server(3366);
    ConnectionF2F netManager;
    netManager.NetworkInfo();

    //Connecting UI widgets with network object code
    connect(ui->connectionToPeer, SIGNAL(clicked()), &peer, SLOT(SlotConnected()));
    connect(ui->lineForTypeText, SIGNAL(returnPressed()), &peer, SLOT(SlotSendToServer()));

    //UI connection
    connect(ui->lineForTypeText, SIGNAL(returnPressed()), ui->lineForTypeText, SLOT(clear()));
    connect(ui->writeWanIpOfPeer, SIGNAL(returnPressed()), ui->writeWanIpOfPeer, SLOT(clear()));
    connect(ui->writeLanIpOfPeer, SIGNAL(returnPressed()), ui->writeLanIpOfPeer, SLOT(clear()));
    connect(ui->writeNickOfPeer, SIGNAL(returnPressed()), ui->writeNickOfPeer, SLOT(clear()));

    //UI style and focus
    ui->writeNickOfPeer->setPlaceholderText("Write here nickname of peer");
    ui->writeWanIpOfPeer->setPlaceholderText("Write here WAN IP of peer");
    ui->writeLanIpOfPeer->setPlaceholderText("Write here LAN IP of peer");
    ui->lineForTypeText->setPlaceholderText("Type here");

    ui->writeNickOfPeer->setMaxLength(15);
    ui->writeWanIpOfPeer->setMaxLength(15);
    ui->writeLanIpOfPeer->setMaxLength(15);
    ui->lineForTypeText->setMaxLength(200);

    ui->writeNickOfPeer->setFocusPolicy(WheelFocus);
    ui->writeWanIpOfPeer->setFocusPolicy(WheelFocus);
    ui->writeLanIpOfPeer->setFocusPolicy(WheelFocus);
    ui->lineForTypeText->setFocusPolicy(WheelFocus);

    ui->textFieldForViewMessages->setFocusPolicy(NoFocus);
    ui->textFieldForViewMessages->setReadOnly(true);
    ui->listWithNickName->setFocusPolicy(ClickFocus);

    return;
}

Freechat::~Freechat()
{
    delete ui;
}

void Freechat::on_showNetworkInfo_clicked(bool checked)
{
    switch(checked)
    {
        case false:
        {
            QMessageBox::information(this, tr("Network Info"),
                                 tr("Your LAN IP address: "), Freechat::yourIp);
        }
            break;
        case true:
        {
            QMessageBox::information(this, tr("Error"),
                                 tr("Check your network connection."));
        }
            break;
    }

    return;
}

void Freechat::on_connectionToPeer_clicked(bool checked)
{
    switch(checked)
    {
        case false:
        {
            QMessageBox::information(this, tr("Connection"),
                                 tr("Connecting to peer..."));
        }
            break;
        case true:
        {
            QMessageBox::information(this, tr("Disconnected"),
                                 tr("Peer does not want to connect with you"));
        }
            break;
    }

    return;
}

void Freechat::on_lineForTypeText_returnPressed()
{
    Freechat::bufferOfMessages += ui->lineForTypeText->text();

    #ifndef Q_DEBUG
    qDebug() << "Freechat class: " << Freechat::bufferOfMessages;
    #endif

    Freechat::bufferOfMessages.clear();

    return;
}

void Freechat::on_writeWanIpOfPeer_returnPressed()
{
    Freechat::wanIpOfPeer += ui->writeWanIpOfPeer->text();

    #ifndef Q_DEBUG
    qDebug() << "Freechat class: " << Freechat::wanIpOfPeer;
    #endif

    Freechat::wanIpOfPeer.clear();

    return;
}

void Freechat::on_writeLanIpOfPeer_returnPressed()
{
    Freechat::lanIpOfPeer += ui->writeLanIpOfPeer->text();

    #ifndef Q_DEBUG
    qDebug() << "Freechat class: " << Freechat::lanIpOfPeer;
    #endif

    Freechat::lanIpOfPeer.clear();

    return;
}

void Freechat::on_writeNickOfPeer_returnPressed()
{
    Freechat::nickNameOfPeer += ui->writeNickOfPeer->text();

    #ifndef Q_DEBUG
    qDebug() << "Freechat class: " << Freechat::nickNameOfPeer;
    #endif

    Freechat::nickNameOfPeer.clear();

    return;
}
