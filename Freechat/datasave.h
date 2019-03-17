/*
***Copyright (C) 2019 Freechat Inc
***Contact: bogdyname@gmail.com
*/

#ifndef DATASAVE_H
#define DATASAVE_H

#include <QTextStream>
#include <QIODevice>
#include <QFile>

class datasave : public QFile
{
    Q_OBJECT

public:
    datasave()
    {

    }
};

#endif // DATASAVE_H
