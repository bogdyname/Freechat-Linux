/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "duinterface.h"
#include "datasave.h"

Duinterface::Duinterface(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    connect(checkUserChooseYes, SIGNAL(UserSelect()),
            this, SLOT(UserSelect()));
    connect(checkUserChooseNo, SIGNAL(UserSelect()),
            this, SLOT(UserSelect()));
    connect( , SIGNAL(CheckYourMemorySize()),
            this, SLOT());
    connect( , SIGNAL(AborProgWheneverMemorySizeFull),
            this, SLOT());

}

void Duinterface::UserSelect()
{
    checkUserChooseNo = /**/;
    checkUserChooseYes = /**/;
}

void Duinterface::AbortProgError()
{
    if (DeleteFile()->count() == 1) // if not return zero
    {
        QMessageBox::information(this, tr("ERROR"),
        tr("Something is wrong! Abort program!"));
    }
    else
    {
        abort();
    }

    if (SaveFile()->count() == 1) // if not return zero
    {
        QMessageBox::information(this, tr("ERROR"),
        tr("Something is wrong! Abort program!"));
    }
    else
    {
        abort();
    }
}

void Duinterface::UserSelectNo()
{
 // will do not write in file
}

void Duinterface::UserSelectYes()
{
 // will do write in file
}
