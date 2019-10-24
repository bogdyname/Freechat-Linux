/********************************************************************************
** Form generated from reading UI file 'freechat.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FREECHAT_H
#define UI_FREECHAT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Freechat
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *writeWanIpOfPeer;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *writeLanIpOfPeer;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *writeNickOfPeer;
    QHBoxLayout *hboxLayout;
    QTextEdit *textFieldForViewMessages;
    QListWidget *listWithNickName;
    QHBoxLayout *hboxLayout1;
    QLabel *labelMessage;
    QLineEdit *lineForTypeText;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *showNetworkInfo;
    QPushButton *connectionToPeer;

    void setupUi(QDialog *Freechat)
    {
        if (Freechat->objectName().isEmpty())
            Freechat->setObjectName(QString::fromUtf8("Freechat"));
        Freechat->resize(625, 484);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        Freechat->setWindowIcon(icon);
        Freechat->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:0, stop:0.392045 rgba(0, 0, 0, 255), stop:0.607955 rgba(255, 255, 255, 255));"));
        gridLayout = new QGridLayout(Freechat);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(9, 9, 9, 9);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(-1, -1, -1, 0);
        writeWanIpOfPeer = new QLineEdit(Freechat);
        writeWanIpOfPeer->setObjectName(QString::fromUtf8("writeWanIpOfPeer"));
        writeWanIpOfPeer->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 57 12pt \"Letter Gothic Std\";"));

        horizontalLayout_6->addWidget(writeWanIpOfPeer);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, -1, -1, 0);
        writeLanIpOfPeer = new QLineEdit(Freechat);
        writeLanIpOfPeer->setObjectName(QString::fromUtf8("writeLanIpOfPeer"));
        writeLanIpOfPeer->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 57 12pt \"Letter Gothic Std\";"));

        horizontalLayout_5->addWidget(writeLanIpOfPeer);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, -1, -1, 0);
        writeNickOfPeer = new QLineEdit(Freechat);
        writeNickOfPeer->setObjectName(QString::fromUtf8("writeNickOfPeer"));
        writeNickOfPeer->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 57 12pt \"Letter Gothic Std\";"));

        horizontalLayout_4->addWidget(writeNickOfPeer);


        verticalLayout->addLayout(horizontalLayout_4);


        gridLayout->addLayout(verticalLayout, 1, 0, 1, 1);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        textFieldForViewMessages = new QTextEdit(Freechat);
        textFieldForViewMessages->setObjectName(QString::fromUtf8("textFieldForViewMessages"));
        textFieldForViewMessages->setFocusPolicy(Qt::NoFocus);
        textFieldForViewMessages->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:0, stop:0.392045 rgba(0, 0, 0, 255), stop:0.607955 rgba(255, 255, 255, 255));\n"
"color: rgb(255, 255, 255);\n"
"font: 57 12pt \"Letter Gothic Std\";\n"
""));
        textFieldForViewMessages->setReadOnly(true);

        hboxLayout->addWidget(textFieldForViewMessages);

        listWithNickName = new QListWidget(Freechat);
        listWithNickName->setObjectName(QString::fromUtf8("listWithNickName"));
        listWithNickName->setMaximumSize(QSize(180, 16777215));
        listWithNickName->setFocusPolicy(Qt::NoFocus);
        listWithNickName->setAutoFillBackground(false);
        listWithNickName->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:0, stop:0.392045 rgba(0, 0, 0, 255), stop:0.607955 rgba(255, 255, 255, 255));\n"
"color: rgb(255, 255, 255);\n"
"font: 57 12pt \"Letter Gothic Std\";"));

        hboxLayout->addWidget(listWithNickName);


        gridLayout->addLayout(hboxLayout, 3, 0, 1, 1);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        labelMessage = new QLabel(Freechat);
        labelMessage->setObjectName(QString::fromUtf8("labelMessage"));
        labelMessage->setStyleSheet(QString::fromUtf8("font: 8pt \"Letter Gothic Std\";\n"
"background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:0, stop:0.392045 rgba(0, 0, 0, 255), stop:0.607955 rgba(255, 255, 255, 255));\n"
"color: rgb(255, 255, 255);"));

        hboxLayout1->addWidget(labelMessage);

        lineForTypeText = new QLineEdit(Freechat);
        lineForTypeText->setObjectName(QString::fromUtf8("lineForTypeText"));
        lineForTypeText->setStyleSheet(QString::fromUtf8("font: 8pt \"Letter Gothic Std\";\n"
"color: rgb(255, 255, 255);\n"
"background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:0, stop:0.392045 rgba(0, 0, 0, 255), stop:0.607955 rgba(255, 255, 255, 255));"));

        hboxLayout1->addWidget(lineForTypeText);


        gridLayout->addLayout(hboxLayout1, 4, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, -1, -1, 0);
        showNetworkInfo = new QPushButton(Freechat);
        showNetworkInfo->setObjectName(QString::fromUtf8("showNetworkInfo"));
        showNetworkInfo->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 57 12pt \"Letter Gothic Std\";"));

        horizontalLayout_3->addWidget(showNetworkInfo);

        connectionToPeer = new QPushButton(Freechat);
        connectionToPeer->setObjectName(QString::fromUtf8("connectionToPeer"));
        connectionToPeer->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 57 12pt \"Letter Gothic Std\";"));

        horizontalLayout_3->addWidget(connectionToPeer);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);


        retranslateUi(Freechat);

        QMetaObject::connectSlotsByName(Freechat);
    } // setupUi

    void retranslateUi(QDialog *Freechat)
    {
        Freechat->setWindowTitle(QApplication::translate("Freechat", "Freechat", nullptr));
        writeWanIpOfPeer->setText(QString());
        writeLanIpOfPeer->setText(QString());
        writeNickOfPeer->setText(QString());
        labelMessage->setText(QApplication::translate("Freechat", "Message", nullptr));
        lineForTypeText->setText(QString());
        showNetworkInfo->setText(QString());
        connectionToPeer->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Freechat: public Ui_Freechat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FREECHAT_H
