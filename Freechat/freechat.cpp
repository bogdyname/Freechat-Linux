/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include <QtWidgets>
#include "freechat.h"

Freechat::Freechat(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    lineEdit->setFocusPolicy(Qt::StrongFocus);
    textEdit->setFocusPolicy(Qt::NoFocus);
    textEdit->setReadOnly(true);
    listWidget->setFocusPolicy(Qt::NoFocus);

    connect(lineEdit, SIGNAL(returnPressed()),
            this, SLOT(returnPressed()));
    connect(lineEdit, SIGNAL(returnPressed()),
            this, SLOT(returnPressed()));
    connect(&userclient, SIGNAL(newMessage(QString,QString)),
            this, SLOT(appendMessage(QString,QString)));
    connect(&userclient, SIGNAL(userIsJoined(QString)),
            this, SLOT(userIsJoined(QString)));
    connect(&userclient, SIGNAL(userIsLeft(QString)),
            this, SLOT(userIsLeft(QString)));

    whoami = userclient.nickName();
    userIsJoined(whoami);
    tableFormat.setBorder(0);
    QTimer::singleShot(10 * 1000, this, SLOT(showInformation()));
}

void Freechat::appendMessage(const QString &from, const QString &message)
{
    if (from.isEmpty() || message.isEmpty())
        return;

    QTextCursor cursor(textEdit->textCursor());
    cursor.movePosition(QTextCursor::End);
    QTextTable *table = cursor.insertTable(1, 2, tableFormat);
    table->cellAt(0, 0).firstCursorPosition().insertText('<' + from + "> ");
    table->cellAt(0, 1).firstCursorPosition().insertText(message);
    QScrollBar *bar = textEdit->verticalScrollBar();
    bar->setValue(bar->maximum());
}

void Freechat::returnPressed()
{
    QString text = lineEdit->text();
    if (text.isEmpty())
    {
        return;
    }
    else
    {
        /*CLEAR CODE*/
    }

    if (text.startsWith(QChar('/')))
    {
        QColor color = textEdit->textColor();
        textEdit->setTextColor(Qt::black);
        textEdit->append(tr("! Unknown command: %1")
                         .arg(text.left(text.indexOf(' '))));
        textEdit->setTextColor(color);
    }
    else
    {
        userclient.sendMessage(text);
        appendMessage(whoami, text);
    }

    lineEdit->clear();
}

void Freechat::userIsJoined(const QString &nick)
{
    if (nick.isEmpty())
    {
        return;
    }
    else
    {
        /*CLEAR CODE*/
    }

    QColor color = textEdit->textColor();
    textEdit->setTextColor(Qt::gray);
    textEdit->append(tr("* %1 has joined").arg(nick));
    textEdit->setTextColor(color);
    listWidget->addItem(nick);
}

void Freechat::userIsLeft(const QString &nick)
{
    if (nick.isEmpty())
    {
        return;
    }
    else
    {
        /*CLEAR CODE*/
    }

    QList<QListWidgetItem *> items = listWidget->findItems(nick, Qt::MatchExactly);
    if (items.isEmpty())
    {
        return;
    }
    else
    {
        /*CLEAR CODE*/
    }

    delete items.at(0);
    QColor color = textEdit->textColor();
    textEdit->setTextColor(Qt::gray);
    textEdit->append(tr("* %1 has left").arg(nick));
    textEdit->setTextColor(color);
}

void Freechat::hiiiiiiBoy()
{
    if (listWidget->count() == 1)
    {
        QMessageBox::information(this, tr("Freechat"),
        tr("Let's try the best! Boy boy - son, son son, boy!"));
    }
    else
    {
        /*CLEAR CODE*/
    }
}
