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

private slots:
    void ReturnPressedWithData();
    void PastInfoIntoCurrency();
    void PastInfoIntoOwnCurrency();
    void PastInfoIntoNetCurrency();
    void PastInfoIntoCurrencyList();

private:
    Ui::WorldCash *ui;
};
#endif
