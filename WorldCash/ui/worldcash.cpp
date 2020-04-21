#include "ui/worldcash.h"

WorldCash::WorldCash(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WorldCash)
{
    WorldCash::ui->setupUi(this);

    //Objects of UI
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

    //Object of own classes1
    try
    {
        WorldCash::managerOfFavorite = new Favorite();
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
    WorldCash::currencyList->QWidget::setMaximumWidth(150);
    WorldCash::currencyList->QWidget::setMinimumWidth(150);

    //third layout
    WorldCash::dataOfCurrency->QWidget::setMinimumSize(150, 30);
    WorldCash::dataOfCurrency->QWidget::setMaximumWidth(150);
    WorldCash::dataOfCurrency->QWidget::setMaximumHeight(30);

    WorldCash::ownCurrency->QWidget::setMinimumSize(25, 30);
    WorldCash::ownCurrency->QWidget::setMaximumHeight(30);

    //CONNECT SIGNALS WITH SLOTS

    //ListWidget
    QObject::connect(WorldCash::currencyList, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(CallFavoriteFromCurrencyList()));


    //TTS
    WorldCash::currencyList->QListWidget::addItem("favorite");
}

WorldCash::~WorldCash()
{
    delete WorldCash::ui;
    delete WorldCash::managerOfFavorite;
    delete WorldCash::ownCurrency;
    delete WorldCash::netCurrency;
    delete WorldCash::currency;
    delete WorldCash::dataOfCurrency;
    delete WorldCash::currencyList;
}

// SLOTS
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

void WorldCash::CallFavoriteFromCurrencyList()
{
    //TTS
    QString lol = "lol";
    QString lol1 = "lol";
    QString lol2 = "lol";

    if(!WorldCash::CheckListOfCurrency())
        return;
    else
        WorldCash::managerOfFavorite->Favorite::DataOfFavorite(lol, lol1, lol2);

    return;
}

// METHODS
bool WorldCash::CheckListOfCurrency()
{
    QList<QListWidgetItem*> items = WorldCash::currencyList->QListWidget::selectedItems();
    unsigned short number = 1;

    foreach(QListWidgetItem *item, items)
        number = WorldCash::currencyList->QListWidget::row(item);

    qDebug() << number;

    if(number)
        return false;
    else
        return true;
}

//TEMPLATES FOR CONTAINER
template <typename Wcontainer>
Wcontainer WorldCash::WriteElementsInList(Wcontainer &list, const QString &element)
{
    return list << element;
}

template <typename Gcontainer>
Gcontainer WorldCash::GetElementsFromList(const Gcontainer &list)
{
    QList<QString>::const_iterator it = list.constBegin();

    for(; it != list.end(); ++it)
    {
        #ifndef Q_DEBUG
        qDebug() << "Element from list: " << *it << endl;
        #endif
    }

    return list;
}

template <typename Rcontainer>
Rcontainer WorldCash::RemoveElementsFromList(Rcontainer &list)
{
    QList<QString>::iterator it = list.begin();

    for(; it != list.end(); ++it)
    {
        #ifndef Q_DEBUG
        qDebug() << "Deleted element from list: " << *it << endl;
        #endif

        list.erase(it);
    }

    return list;
}

