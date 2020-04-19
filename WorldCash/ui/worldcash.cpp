#include "ui/worldcash.h"

WorldCash::WorldCash(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WorldCash)
{
    WorldCash::ui->setupUi(this);

    try {
        WorldCash::ownCurrency = new QTextBrowser();
        WorldCash::netCurrency = new QTextBrowser();
        WorldCash::dollarCurrency = new QTextBrowser();
        WorldCash::euroCurrency = new QTextBrowser();
        WorldCash::poundCurrency = new QTextBrowser();
        WorldCash::dataOfCurrency = new QLineEdit();
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

    //first layout
    WorldCash::ui->layoutOfNetwrok->QVBoxLayout::addWidget(WorldCash::ownCurrency);
    WorldCash::ui->layoutOfNetwrok->QVBoxLayout::addWidget(WorldCash::netCurrency);

    //second layout
    WorldCash::ui->layoutOfMath->QHBoxLayout::addWidget(WorldCash::dollarCurrency);
    WorldCash::ui->layoutOfMath->QHBoxLayout::addWidget(WorldCash::euroCurrency);
    WorldCash::ui->layoutOfMath->QHBoxLayout::addWidget(WorldCash::poundCurrency);

    //third layout
    WorldCash::ui->layoutOfData->QVBoxLayout::addWidget(WorldCash::dataOfCurrency);

    WorldCash::ownCurrency->QWidget::maximumWidth();
    WorldCash::ownCurrency->QWidget::setMaximumHeight(30);

    WorldCash::netCurrency->QWidget::maximumWidth();
    WorldCash::netCurrency->QWidget::setMaximumHeight(30);
}

WorldCash::~WorldCash()
{
    delete WorldCash::ui;
}

