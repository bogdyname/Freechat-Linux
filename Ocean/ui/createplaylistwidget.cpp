#include "createplaylistwidget.h"

CreatePlayListWidget::CreatePlayListWidget(QWidget *parent)
    : QWidget(parent)
{
    CreatePlayListWidget::ui->setupUi(this);

    try
    {
        //Objects of UI
        CreatePlayListWidget::nameOfPlayList = new QLineEdit();
        CreatePlayListWidget::okay = new QPushButton("okay");
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
    CreatePlayListWidget::ui->horizontalLayout->QHBoxLayout::addWidget(CreatePlayListWidget::okay);
    CreatePlayListWidget::ui->horizontalLayout->QHBoxLayout::addWidget(CreatePlayListWidget::cancel);

    //SIGNALS/SLOTS
    QObject::connect(CreatePlayListWidget::nameOfPlayList, &QLineEdit::returnPressed, this, &CreatePlayListWidget::ReturnPressedForLineEdit);
    QObject::connect(CreatePlayListWidget::okay, &QPushButton::clicked, this, &CreatePlayListWidget::ClickedOkay);
    QObject::connect(CreatePlayListWidget::cancel, &QPushButton::clicked, this, &CreatePlayListWidget::ClickedCancel);

    return;
}

CreatePlayListWidget::~CreatePlayListWidget()
{
    delete CreatePlayListWidget::nameOfPlayList;
    delete CreatePlayListWidget::okay;
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

    return;
}

void CreatePlayListWidget::ClickedOkay()
{
    if(CreatePlayListWidget::createName == "")
        return;

    emit CreatePlayListWidget::SendNameOfPlayList(CreatePlayListWidget::createName);

    return;
}

void CreatePlayListWidget::ClickedCancel()
{
    emit CreatePlayListWidget::BreakeWidget();

    return;
}
