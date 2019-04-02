/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef DUINTERFACE_H
#define DUINTERFACE_H

#include <QWidget>
#include <QTextList>
#include "datasave.h"
#include "username.h"
#include "usernametable.h"

class Username;
class Usernametable;

class Duinterface : public QWidget, private Ui::Duinterface
{
    Q_OBJECT

public:
    Duinterface(QWidget *parent = nullptr);

public slots:
    bool UserSelect();

private slots:

};

#endif // DUINTERFACE_H
