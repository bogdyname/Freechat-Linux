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

    //Network
    Peerout peer;
    Peerin server(3366);
    ConnectionF2F netManager;
    netManager.NetworkInfo();

    //Bin
    Bin bin;

    //variables for pointer of function from ConnectionF2F
    checkNetworkConnection = ConnectionF2F::CheckConnection;

    //close all QLineEdit if network shutdown
    switch((*checkNetworkConnection)())
    {
        case 101:
        {
            #ifndef Q_DEBUG
            qDebug() << "Network access";
            #endif
        }
        break;
        case 404:
        {
            //block all field without network access
            ui->writeNickOfPeer->setReadOnly(true);
            ui->writeWanIpOfPeer->setReadOnly(true);
            ui->writeLanIpOfPeer->setReadOnly(true);
            ui->lineForTypeText->setReadOnly(true);
        }
        break;
    }

    //Connecting UI widgets with bin code
    connect(ui->writeNickOfPeer, SIGNAL(returnPressed()), &bin, SLOT(AddPeerNick()));
    connect(ui->writeLanIpOfPeer, SIGNAL(returnPressed()), &bin, SLOT(AddPeerLan()));
    connect(ui->writeWanIpOfPeer, SIGNAL(returnPressed()), &bin, SLOT(AddPeerWan()));
    connect(ui->listWithNickName, SIGNAL(itemClicked(QListWidgetItem)), &bin, SLOT(GetNickname(QList)));
    connect(ui->listWithNickName, SIGNAL(itemDoubleClicked(QListWidgetItem)), &bin, SLOT(DeletePeer()));

    //Connecting UI widgets with network object code
    connect(ui->connectionToPeer, SIGNAL(clicked()), &peer, SLOT(SlotConnected()));
    connect(ui->lineForTypeText, SIGNAL(returnPressed()), &peer, SLOT(SlotSendToServer()));

    //UI connection
    connect(ui->lineForTypeText, SIGNAL(returnPressed()), ui->lineForTypeText, SLOT(clear()));
    connect(ui->writeWanIpOfPeer, SIGNAL(returnPressed()), ui->writeWanIpOfPeer, SLOT(clear()));
    connect(ui->writeLanIpOfPeer, SIGNAL(returnPressed()), ui->writeLanIpOfPeer, SLOT(clear()));
    connect(ui->writeNickOfPeer, SIGNAL(returnPressed()), ui->writeNickOfPeer, SLOT(clear()));
    connect(ui->showNetworkInfo, SIGNAL(clicked(bool)), ui->showNetworkInfo, SLOT(setChecked(bool)));
    connect(ui->connectionToPeer, SIGNAL(clicked(bool)), ui->connectionToPeer, SLOT(setChecked(bool)));

    //UI style and focus
    ui->showNetworkInfo->setText("Info of Network");
    ui->connectionToPeer->setText("Connecting to peer");
    ui->lineForTypeText->setPlaceholderText("Type here");
    ui->writeNickOfPeer->setPlaceholderText("Write here nickname of peer");
    ui->writeWanIpOfPeer->setPlaceholderText("Write here WAN IP of peer");
    ui->writeLanIpOfPeer->setPlaceholderText("Write here LAN IP of peer");

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
    if(ui != nullptr)
    {
        delete ui;
    }
    else
    {
        /*clear code*/
    }

    return;
}

void Freechat::on_showNetworkInfo_clicked()
{
    QString status = QString("<h1>Your LAN IP address: %1</h1>").arg(Freechat::yourIp);

    switch((*checkNetworkConnection)())
    {
        case 101:
        {
            QMessageBox::information(this, tr("<title>Network Info</title>"),
                             status, "ok");
        }
        break;
        case 404:
        {
            QMessageBox::critical(this, tr("<title>Error</title>"),
                             tr("<h1>Check your network connection.</h1>"), "ok");
        }
        break;
    }

    return;
}

void Freechat::on_connectionToPeer_clicked() // do nto use this button now, bc it crashing all system
{
    //checkConnection = ; need make f() for check connection to peer and passing it like * of f() to here

    bool ok = false;

    if(ok == true)
    {
        QMessageBox::information(this, tr("<title>Connection</title>"),
                             tr("<h1>Connecting to peer...</h1>"), "ok");
    }
    else
    {
        QMessageBox::critical(this, tr("<title>Error</title>"),
                             tr("<h1>Error connecting to peer.</h1>"), "ok");
    }

    return;
}

void Freechat::on_lineForTypeText_returnPressed()
{
    Freechat::bufferOfMessages += ui->lineForTypeText->text();

    #ifndef Q_DEBUG
    qDebug() << "Freechat class: " << Freechat::bufferOfMessages;
    #endif

    //Freechat::bufferOfMessages.clear();

    return;
}

void Freechat::on_writeWanIpOfPeer_returnPressed()
{
    Freechat::wanIpOfPeer += ui->writeWanIpOfPeer->text();

    #ifndef Q_DEBUG
    qDebug() << "Freechat class: " << Freechat::wanIpOfPeer;
    #endif

    //Freechat::wanIpOfPeer.clear();

    return;
}

void Freechat::on_writeLanIpOfPeer_returnPressed()
{
    Freechat::lanIpOfPeer += ui->writeLanIpOfPeer->text();

    #ifndef Q_DEBUG
    qDebug() << "Freechat class: " << Freechat::lanIpOfPeer;
    #endif

    //Freechat::lanIpOfPeer.clear();

    return;
}

void Freechat::on_writeNickOfPeer_returnPressed()
{
    Freechat::nickNameOfPeer += ui->writeNickOfPeer->text();

    #ifndef Q_DEBUG
    qDebug() << "Freechat class: " << Freechat::nickNameOfPeer;
    #endif

    //Freechat::nickNameOfPeer.clear();

    return;
}

void Freechat::on_listWithNickName_itemDoubleClicked(QListWidgetItem *item)
{

    return;
}

void Freechat::on_listWithNickName_itemClicked(QListWidgetItem *item)
{

    return;
}
