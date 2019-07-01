/********************************************************************************
** Form generated from reading UI file 'freechat.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FREECHAT_H
#define UI_FREECHAT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Freechat
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *hboxLayout;
    QTextEdit *textFieldForViewMessages;
    QListWidget *listWithNicknameOfUser;
    QTextEdit *listViewWithNetworkData;
    QHBoxLayout *hboxLayout1;
    QLabel *labelMessage;
    QLineEdit *lineForTypeText;

    void setupUi(QDialog *Freechat)
    {
        if (Freechat->objectName().isEmpty())
            Freechat->setObjectName(QString::fromUtf8("Freechat"));
        Freechat->resize(620, 483);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../freechat.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        Freechat->setWindowIcon(icon);
        Freechat->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:0, stop:0.392045 rgba(0, 0, 0, 255), stop:0.607955 rgba(255, 255, 255, 255));"));
        verticalLayout = new QVBoxLayout(Freechat);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(9, 9, 9, 9);
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        textFieldForViewMessages = new QTextEdit(Freechat);
        textFieldForViewMessages->setObjectName(QString::fromUtf8("textFieldForViewMessages"));
        textFieldForViewMessages->setFocusPolicy(Qt::NoFocus);
        textFieldForViewMessages->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:0, stop:0.392045 rgba(0, 0, 0, 255), stop:0.607955 rgba(255, 255, 255, 255));\n"
""));
        textFieldForViewMessages->setReadOnly(true);

        hboxLayout->addWidget(textFieldForViewMessages);

        listWithNicknameOfUser = new QListWidget(Freechat);
        listWithNicknameOfUser->setObjectName(QString::fromUtf8("listWithNicknameOfUser"));
        listWithNicknameOfUser->setMaximumSize(QSize(180, 16777215));
        listWithNicknameOfUser->setFocusPolicy(Qt::NoFocus);
        listWithNicknameOfUser->setAutoFillBackground(false);
        listWithNicknameOfUser->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:0, stop:0.392045 rgba(0, 0, 0, 255), stop:0.607955 rgba(255, 255, 255, 255));"));

        hboxLayout->addWidget(listWithNicknameOfUser);

        listViewWithNetworkData = new QTextEdit(Freechat);
        listViewWithNetworkData->setObjectName(QString::fromUtf8("listViewWithNetworkData"));
        listViewWithNetworkData->setMaximumSize(QSize(150, 16777215));
        listViewWithNetworkData->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:0, stop:0.392045 rgba(0, 0, 0, 255), stop:0.607955 rgba(255, 255, 255, 255));"));

        hboxLayout->addWidget(listViewWithNetworkData);


        verticalLayout->addLayout(hboxLayout);

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
        lineForTypeText->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:0, stop:0.392045 rgba(0, 0, 0, 255), stop:0.607955 rgba(255, 255, 255, 255));"));

        hboxLayout1->addWidget(lineForTypeText);


        verticalLayout->addLayout(hboxLayout1);


        retranslateUi(Freechat);

        QMetaObject::connectSlotsByName(Freechat);
    } // setupUi

    void retranslateUi(QDialog *Freechat)
    {
        Freechat->setWindowTitle(QApplication::translate("Freechat", "Freechat", nullptr));
        labelMessage->setText(QApplication::translate("Freechat", "Message", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Freechat: public Ui_Freechat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FREECHAT_H
