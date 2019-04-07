/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "filecompression.h"

Filecompression::Filecompression(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    connect( , SIGNAL(ChooseFileFromMemory()),
             this, SLOT(UserSelect()));
    connect( , SIGNAL(ChooseFileFromMemory()),
             this, SLOT(ConfirmCompression()));
    connect( , SIGNAL(ChooseFileFromMemory()),
             this, SLOT(UserCelectOfCompression()));
}

QFile Filecompression::ChooseFileFromMemory()
{

}

QFile Filecompression::AlgorithmOfFileCompression()
{

}

void Filecompression::UserSelectOfTypeFile()
{

}

void Filecompression::UserCelectOfCompression()
{

}

void Filecompression::ConfirmCompression()
{

}
