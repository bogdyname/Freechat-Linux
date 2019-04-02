/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include "ui_multimedia.h"
#include "videoviewer.h"
#include <QWidget>

class Multimedia : public QWidget , private Ui::Multimedia
{
    Q_OBJECT

public:
    Multimedia();
};

#endif // MULTIMEDIA_H
