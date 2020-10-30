/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#include "getstringwidget.h"

GetStringWidget::GetStringWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GetString)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->hide();

    try
    {
        //Objects of UI
        lineEditForString = new QLineEdit(this);
        cancel = new QPushButton("cancel", this);
    }
    catch(...)
    {
        qCritical() << "Some exception caught";
        exit(1);
    }

    getString = "";

    //Ui settings
    ui->horizontalLayout->addWidget(lineEditForString);
    ui->horizontalLayout->addWidget(cancel);

    //SIGNALS/SLOTS
    //QLineEdit
    connect(lineEditForString, &QLineEdit::returnPressed, this, &GetStringWidget::ReturnPressedForLineEdit);
    connect(lineEditForString, &QLineEdit::returnPressed, lineEditForString, &QLineEdit::clear);
    //Button
    connect(cancel, &QPushButton::clicked, this, &GetStringWidget::ClickedCancel);

    return;
}

GetStringWidget::~GetStringWidget()
{
    delete ui;

    qDebug() << "Destructor from GetStringWidget.cpp";
}

QString GetStringWidget::GetNameOfNewPlayList()
{
    return getString;
}

void GetStringWidget::ReturnPressedForLineEdit()
{
    if(lineEditForString->text() == "")
        return;

    getString.clear();
    getString += lineEditForString->text();
    emit this->SendName();

    return;
}

void GetStringWidget::ClickedCancel()
{
    emit this->BreakeWidget();

    return;
}
