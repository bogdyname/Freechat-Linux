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

#include "ui_getstring.h"

class GetStringWidget : public QWidget, private Ui::GetString
{
    Q_OBJECT

public:
    GetStringWidget(QWidget *parent = nullptr);
    ~GetStringWidget();

private:
    QLineEdit *lineEditForString = nullptr;
    QPushButton *cancel = nullptr;

signals:
    void SendName(const QString &name);
    void BreakeWidget();

public:
    QString GetNameOfNewPlayList();

private slots:
    void ReturnPressedForLineEdit();
    void ClickedCancel();

private:
    QString getString;

private:
    Ui::GetString *ui;
};

#endif
