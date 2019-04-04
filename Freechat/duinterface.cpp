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
    checkUserChooseNo = /**/;
    checkUserChooseYes = /**/;
}

void Duinterface::AbortProgError()
{
    abort();
}

void Duinterface::UserSelectNo()
{
 // will do not write in file
}

void Duinterface::UserSelectYes()
{
 // will do write in file
}
