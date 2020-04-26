#ifndef WORLDCASH_H
#define WORLDCASH_H

#include <QDebug>
#include <QWidget>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QMainWindow>
#include <QStringList>
#include <QTextBrowser>
#include <QMessageBox>
#include "ui_worldcash.h"

class Ocean : public QMainWindow, private Ui::WorldCash
{
    Q_OBJECT

public:
    Ocean(QWidget *parent = nullptr);
    ~Ocean();

private:
    QListWidget *listMusic;


private:
    Ui::WorldCash *ui;
};
#endif
