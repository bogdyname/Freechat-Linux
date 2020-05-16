/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#ifndef CREATEPLAYLISTWIDGET_H
#define CREATEPLAYLISTWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>

#include "ui_createplaylist.h"

class CreatePlayListWidget : public QDialog, private Ui::CreatePlayList
{
    Q_OBJECT

public:
    CreatePlayListWidget(QDialog *parent = nullptr);
    ~CreatePlayListWidget();

private:
    QLineEdit *nameOfPlayList = nullptr;
    QPushButton *cancel = nullptr;

signals:
    void SendNameOfPlayList(const QString &name);
    void BreakeWidget();

private slots:
    void ReturnPressedForLineEdit();
    void ClickedCancel();

private:
    QString createName;

private:
    Ui::CreatePlayList *ui;
};

#endif
