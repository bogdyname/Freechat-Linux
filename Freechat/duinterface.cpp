/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "duinterface.h"

Duinterface::Duinterface(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    connect(checkUserChooseYes, SIGNAL(UserSelect()),
            this, SLOT(UserSelect()));
    connect(checkUserChooseNo, SIGNAL(UserSelect()),
            this, SLOT(UserSelect()));
}

bool Duinterface::UserSelect()
{

}
