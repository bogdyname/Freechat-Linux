#ifndef WORLDCASH_H
#define WORLDCASH_H

#include <QDebug>
#include <QWidget>
#include <QLineEdit>
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
    QTextBrowser *dollarCurrency;
    QTextBrowser *euroCurrency;
    QTextBrowser *poundCurrency;
    QLineEdit *dataOfCurrency;

private:
    Ui::WorldCash *ui;
};
#endif
