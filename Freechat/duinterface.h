/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef DUINTERFACE_H
#define DUINTERFACE_H

#include <QWidget>
#include <QFile>

class Duinterface : public QFile, private Ui::Duinterface
{
public:
    Duinterface();

public slots:
    bool UserSelect();
};

#endif // DUINTERFACE_H
