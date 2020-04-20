#ifndef WORLDCASH_H
#define WORLDCASH_H

#include <QDebug>
#include <QWidget>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QMainWindow>
#include <QTextBrowser>
#include "ui_worldcash.h"
#include "ui/favorite.h"

class WorldCash : public QMainWindow, private Ui::WorldCash
{
    Q_OBJECT

public:
    WorldCash(QWidget *parent = nullptr);
    ~WorldCash();

private:
    QTextBrowser *ownCurrency;
    QTextBrowser *netCurrency;
    QTextBrowser *currency;
    QLineEdit *dataOfCurrency;
    QListWidget *currencyList;

    //Object
private:
    Favorite *managerOfFavorite;

private slots:
    void ReturnPressedWithData();
    void PastInfoIntoCurrency();
    void PastInfoIntoOwnCurrency();
    void PastInfoIntoNetCurrency();
    void CallFavoriteFromCurrencyList();

private:
    bool CheckListOfCurrency();

private:
    template <typename Wcontainer>
    Wcontainer WriteElementsInList(Wcontainer &list, const QString &element);

    template <typename Gcontainer>
    Gcontainer GetElementsFromList(const Gcontainer &list);

    template <typename Rcontainer>
    Rcontainer RemoveElementsFromList(Rcontainer &list);

private:
    Ui::WorldCash *ui;
};
#endif
