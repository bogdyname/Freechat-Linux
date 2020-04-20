#include "ui/favorite.h"

Favorite::Favorite(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Favorite)
{
    Favorite::ui->setupUi(this);

    QWidget::setMinimumSize(250, 250);
    QWidget::setMaximumSize(500, 500);

    try
    {
        Favorite::favoriteOne = new QTextBrowser();
        Favorite::favoriteTwo = new QTextBrowser();
        Favorite::favoriteThree = new QTextBrowser();
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

    Favorite::ui->horizontalLayout->QHBoxLayout::addWidget(Favorite::favoriteOne);
    Favorite::ui->horizontalLayout->QHBoxLayout::addWidget(Favorite::favoriteTwo);
    Favorite::ui->horizontalLayout->QHBoxLayout::addWidget(Favorite::favoriteThree);

    return;
}

Favorite::~Favorite()
{
    delete Favorite::ui;
}

void Favorite::DataOfFavorite(const QString &dataOne, const QString &dataTwo, const QString &dataThree)
{
    QWidget::show();
    QWidget::raise();

    return;
}
