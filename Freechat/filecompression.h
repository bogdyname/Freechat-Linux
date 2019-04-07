/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef FILECOMPRESSION_H
#define FILECOMPRESSION_H

#include "ui_compression.h"
#include <QTextStream>
#include <QSaveFile>
#include <QDialog>
#include <QFile>

class Freechat;
class Datasave;
class Duinterface;

class Filecompression : public QDialog , private Ui::Compression
{
    Q_OBJECT

public:
    Filecompression(QWidget *parent = nullptr);

    QFile AlgorithmOfFileCompression();

public slots:
    void UserSelectOfTypeFile();
    void UserCelectOfCompression();
    void ConfirmCompression();

signals:
    QFile ChooseFileFromMemory();
};

#endif // FILECOMPRESSION_H
