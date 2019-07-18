/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef NETWORKSETTINGS_H
#define NETWORKSETTINGS_H

#include "Bin/freechat.h"
#include <QWidget>

class NetworkSettings : public Freechat
{
    Q_OBJECT

public:
    explicit NetworkSettings(QWidget *parent = nullptr);

signals:

public slots:
};

#endif
