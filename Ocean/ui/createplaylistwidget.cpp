/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#include "createplaylistwidget.h"

CreatePlayListWidget::CreatePlayListWidget(QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::CreatePlayList)
{
    CreatePlayListWidget::ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    try
    {
        //Objects of UI
        CreatePlayListWidget::nameOfPlayList = new QLineEdit();
        CreatePlayListWidget::cancel = new QPushButton("cancel");
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

    CreatePlayListWidget::createName = "";

    //Ui settings
    CreatePlayListWidget::ui->verticalLayout->QVBoxLayout::addWidget(CreatePlayListWidget::nameOfPlayList);
    CreatePlayListWidget::ui->horizontalLayout->QHBoxLayout::addWidget(CreatePlayListWidget::cancel);

    //SIGNALS/SLOTS
    //QLineEdit
    QObject::connect(CreatePlayListWidget::nameOfPlayList, &QLineEdit::returnPressed, this, &CreatePlayListWidget::ReturnPressedForLineEdit);
    QObject::connect(CreatePlayListWidget::nameOfPlayList, &QLineEdit::returnPressed, CreatePlayListWidget::nameOfPlayList, &QLineEdit::clear);
    //Buttons
    QObject::connect(CreatePlayListWidget::cancel, &QPushButton::clicked, this, &CreatePlayListWidget::ClickedCancel);

    return;
}

CreatePlayListWidget::~CreatePlayListWidget()
{
    delete CreatePlayListWidget::nameOfPlayList;
    delete CreatePlayListWidget::cancel;
    delete CreatePlayListWidget::ui;

    return;
}

void CreatePlayListWidget::ReturnPressedForLineEdit()
{
    if(CreatePlayListWidget::nameOfPlayList->QLineEdit::text() == "")
        return;

    CreatePlayListWidget::createName.QString::clear();
    CreatePlayListWidget::createName += CreatePlayListWidget::nameOfPlayList->QLineEdit::text();
    emit CreatePlayListWidget::SendNameOfPlayList(CreatePlayListWidget::createName);

    return;
}

void CreatePlayListWidget::ClickedCancel()
{
    emit CreatePlayListWidget::BreakeWidget();

    return;
}
