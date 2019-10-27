/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Bin/bin.h"
#include "Bin/freechat.h"
#include "Network/connectionf2f.h"
#include <QTimer>
#include <QPointer>

 QString Freechat::globalBuffer;
 QString Freechat::viewField;
 QString Freechat::yourIp;
 QString Freechat::lanIpOfPeer;
 QString Freechat::wanIpOfPeer;
 QString Freechat::nickNameOfPeer;
 QString Freechat::bufferOfMessages;

 static QPointer<Peerin> server = nullptr;

Freechat::Freechat(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::Freechat)
{
    ui->setupUi(this);

    //Bin
    Bin bin;

    //Connecting UI widgets with bin code
    connect(ui->writeNickOfPeer, SIGNAL(returnPressed()), &bin, SLOT(AddPeerNick()));
    connect(ui->writeLanIpOfPeer, SIGNAL(returnPressed()), &bin, SLOT(AddPeerLan()));
    connect(ui->writeWanIpOfPeer, SIGNAL(returnPressed()), &bin, SLOT(AddPeerWan()));

    //Network
    Peerout peerout;
    ConnectionF2F netManager;
    netManager.NetworkInfo();
    server = new Peerin;

    QTimer *timer = new QTimer;
    timer->setInterval(10000);
    connect(timer, SIGNAL(timeout()), this, SLOT(ServerStillWorking()));
    timer->start();

    //Connecting UI widgets with network object code
    connect(ui->lineForTypeText, SIGNAL(returnPressed()), &peerout, SLOT(SlotSendToServer()));
    connect(ui->lineForTypeText, SIGNAL(returnPressed()), server, SLOT(SendToClientFlush()));

    //UI connection
    connect(ui->lineForTypeText, SIGNAL(returnPressed()), ui->lineForTypeText, SLOT(clear()));
    connect(ui->writeWanIpOfPeer, SIGNAL(returnPressed()), ui->writeWanIpOfPeer, SLOT(clear()));
    connect(ui->writeLanIpOfPeer, SIGNAL(returnPressed()), ui->writeLanIpOfPeer, SLOT(clear()));
    connect(ui->writeNickOfPeer, SIGNAL(returnPressed()), ui->writeNickOfPeer, SLOT(clear()));

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
    ui->lineForTypeText->setMaxLength(1500);

    ui->writeNickOfPeer->setFocusPolicy(WheelFocus);
    ui->writeWanIpOfPeer->setFocusPolicy(WheelFocus);
    ui->writeLanIpOfPeer->setFocusPolicy(WheelFocus);
    ui->lineForTypeText->setFocusPolicy(WheelFocus);

    ui->textFieldForViewMessages->setFocusPolicy(NoFocus);
    ui->textFieldForViewMessages->setReadOnly(true);
    ui->listWithNickName->setFocusPolicy(ClickFocus);

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

//check server
void Freechat::ServerStillWorking()
{
    if(server != nullptr)
    {
        #ifndef Q_DEBUG
        qDebug() << "Server still working";
        #endif
    }
    else
    {
        #ifndef Q_DEBUG
        qDebug() << "Server stoped!" ;
        #endif
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
            QMessageBox::information(ui->showNetworkInfo, tr("Network Info"),
                             status, "ok");
        }
        break;
        case 404:
        {
            QMessageBox::critical(ui->showNetworkInfo, tr("Error"),
                             tr("<h1>Check your network connection.</h1>"), "ok");
        }
        break;
    }

    return;
}

void Freechat::on_lineForTypeText_returnPressed()
{
    QTime time = QTime::currentTime();
    Freechat::bufferOfMessages += ui->lineForTypeText->text();
    ui->textFieldForViewMessages->insertPlainText("Me:" + time.toString() +
                                 ": " + Freechat::bufferOfMessages + "\n");

    Freechat::bufferOfMessages.clear();//clear in netwrok code

    return;
}

void Freechat::on_writeWanIpOfPeer_returnPressed()
{
    Freechat::wanIpOfPeer += ui->writeWanIpOfPeer->text();

    #ifndef Q_DEBUG
    qDebug() << "Freechat class: " << Freechat::wanIpOfPeer;
    #endif

    return;
}

void Freechat::on_writeLanIpOfPeer_returnPressed()
{
    Freechat::lanIpOfPeer += ui->writeLanIpOfPeer->text();

    #ifndef Q_DEBUG
    qDebug() << "Freechat class: " << Freechat::lanIpOfPeer;
    #endif

    return;
}

void Freechat::on_writeNickOfPeer_returnPressed()
{
    Freechat::nickNameOfPeer += ui->writeNickOfPeer->text();

    #ifndef Q_DEBUG
    qDebug() << "Freechat class: " << Freechat::nickNameOfPeer;
    #endif

    return;
}

void Freechat::on_connectionToPeer_clicked()
{
    Peerout peerout;

    if(Freechat::lanIpOfPeer != "")
    {
        peerout.SlotConnecting();
        QMessageBox::information(ui->connectionToPeer, tr("Connecting"),
                         tr("<h1>Connecting to peer.</h1>"), "ok");
    }
    else
    {
        QMessageBox::critical(ui->connectionToPeer, tr("Connecting error"),
                         tr("<h1>Check IP of peer.</h1>"), "ok");
    }

    return;
}
