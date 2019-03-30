/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef DATASAVE_H
#define DATASAVE_H

#include <QTextStream>
#include <QSaveFile>
#include <QIODevice>
#include <QFile>

class Datasave : public QSaveFile
{
    Q_OBJECT

public:
    Datasave(QObject *parent = nullptr);
};

#endif // DATASAVE_H
