#ifndef FAVORITE_H
#define FAVORITE_H

#include <QDebug>
#include <QWidget>
#include <QTextBrowser>
#include "ui_favorite.h"

class Favorite : public QWidget, private Ui::Favorite
{
    Q_OBJECT

public:
    Favorite(QWidget *parent = nullptr);
    ~Favorite();

private:
    QTextBrowser *favoriteOne;
    QTextBrowser *favoriteTwo;
    QTextBrowser *favoriteThree;

public slots:
    void DataOfFavorite(const QString &dataOne, const QString &dataTwo, const QString &dataThree);

private:
    Ui::Favorite *ui;
};

#endif
