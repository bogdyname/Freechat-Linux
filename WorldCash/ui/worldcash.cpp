#include "ui/worldcash.h"

WorldCash::WorldCash(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WorldCash)
{
    WorldCash::ui->setupUi(this);

    try
    {
        WorldCash::ownCurrency = new QTextBrowser();
        WorldCash::netCurrency = new QTextBrowser();
        WorldCash::currency = new QTextBrowser();
        WorldCash::dataOfCurrency = new QLineEdit();
        WorldCash::currencyList = new QListWidget();
    }
    catch (std::bad_alloc &exp)
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

    //LAYOUTS
    //first layout
    WorldCash::ui->layoutOfNetwrok->QHBoxLayout::addWidget(WorldCash::netCurrency);

    //second layout
    WorldCash::ui->layoutOfMath->QHBoxLayout::addWidget(WorldCash::currencyList);
    WorldCash::ui->layoutOfMath->QHBoxLayout::addWidget(WorldCash::currency);

    //third layout
    WorldCash::ui->layoutOfData->QHBoxLayout::addWidget(WorldCash::dataOfCurrency);
    WorldCash::ui->layoutOfData->QHBoxLayout::addWidget(WorldCash::ownCurrency);

    //STYLE
    //first layout
    WorldCash::netCurrency->QWidget::maximumWidth();
    WorldCash::netCurrency->QWidget::setMaximumHeight(30);

    //second layout
    WorldCash::currency->QWidget::setMinimumSize(150, 150);

    //third layout
    WorldCash::dataOfCurrency->QWidget::setMinimumSize(25, 30);
    WorldCash::dataOfCurrency->QWidget::setMaximumHeight(30);
    WorldCash::ownCurrency->QWidget::setMinimumSize(25, 30);
    WorldCash::ownCurrency->QWidget::setMaximumHeight(30);

    //CONNECT SIGNALS WITH SLOTS
}

WorldCash::~WorldCash()
{
    delete WorldCash::ui;
}

void WorldCash::ReturnPressedWithData()
{
    if(WorldCash::dataOfCurrency->QLineEdit::text() == "")
        return;

    return;
}

void WorldCash::PastInfoIntoCurrency()
{

    return;
}

void WorldCash::PastInfoIntoOwnCurrency()
{

    return;
}

void WorldCash::PastInfoIntoNetCurrency()
{

    return;
}

void WorldCash::PastInfoIntoCurrencyList()
{

    return;
}

