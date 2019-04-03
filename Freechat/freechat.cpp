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

    connect(lineEdit, SIGNAL(ReturnPressed()),
            this, SLOT(ReturnPressed()));
    connect(lineEdit, SIGNAL(ReturnPressed()),
            this, SLOT(ReturnPressed()));
    connect(&userclient, SIGNAL(NewMessage(QString,QString)),
            this, SLOT(AppendMessage(QString,QString)));
    connect(&userclient, SIGNAL(UserIsJoined(QString)),
            this, SLOT(UserIsJoined(QString)));
    connect(&userclient, SIGNAL(UserIsLeft(QString)),
            this, SLOT(UserIsLeft(QString)));

    whoami = userclient.NickName();
    UserIsJoined(whoami);
    tableFormat.setBorder(0);
    QTimer::singleShot(10 * 1000, this, SLOT(showInformation()));
}

void Freechat::AppendMessage(const QString &from, const QString &message)
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

void Freechat::ReturnPressed()
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
        userclient.SendMessage(text);
        AppendMessage(whoami, text);
    }

    lineEdit->clear();
}

void Freechat::UserIsJoined(const QString &nick)
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

void Freechat::UserIsLeft(const QString &nick)
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

void Freechat::HiiiiiiBoy()
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
