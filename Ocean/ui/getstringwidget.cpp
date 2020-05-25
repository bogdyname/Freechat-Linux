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
    GetStringWidget::ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    try
    {
        //Objects of UI
        GetStringWidget::lineEditForString = new QLineEdit();
        GetStringWidget::cancel = new QPushButton("cancel");
    }
    catch(std::bad_alloc &exp)
    {
        #ifndef Q_DEBUG
        qCritical() << "Exception caught: " << exp.std::bad_alloc::what();
        #endif
        abort();
    }
    catch(...)
    {
        #ifndef Q_DEBUG
        qCritical() << "Some exception caught";
        #endif
        abort();
    }

    GetStringWidget::getString = "";

    //Ui settings
    GetStringWidget::ui->verticalLayout->QVBoxLayout::addWidget(GetStringWidget::lineEditForString);
    GetStringWidget::ui->horizontalLayout->QHBoxLayout::addWidget(GetStringWidget::cancel);

    //SIGNALS/SLOTS
    //QLineEdit
    QObject::connect(GetStringWidget::lineEditForString, &QLineEdit::returnPressed, this, &GetStringWidget::ReturnPressedForLineEdit);
    QObject::connect(GetStringWidget::lineEditForString, &QLineEdit::returnPressed, GetStringWidget::lineEditForString, &QLineEdit::clear);
    //Button
    QObject::connect(GetStringWidget::cancel, &QPushButton::clicked, this, &GetStringWidget::ClickedCancel);

    return;
}

GetStringWidget::~GetStringWidget()
{
    delete GetStringWidget::lineEditForString;
    delete GetStringWidget::cancel;
    delete GetStringWidget::ui;

    return;
}

void GetStringWidget::ReturnPressedForLineEdit()
{
    if(GetStringWidget::lineEditForString->QLineEdit::text() == "")
        return;

    GetStringWidget::getString.QString::clear();
    GetStringWidget::getString += GetStringWidget::lineEditForString->QLineEdit::text();
    emit this->GetStringWidget::SendName(GetStringWidget::getString);

    return;
}

void GetStringWidget::ClickedCancel()
{
    emit this->GetStringWidget::BreakeWidget();

    return;
}
