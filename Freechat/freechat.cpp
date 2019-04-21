/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include <QtWidgets>
#include "freechat.h"

using namespace Qt;

Freechat::Freechat(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    lineForTypeText->setFocusPolicy(StrongFocus);
    textFieldForViewMessages->setFocusPolicy(NoFocus);
    textFieldForViewMessages->setReadOnly(true);
    listWithNicknameOfUser->setFocusPolicy(NoFocus);

    connect(lineForTypeText, SIGNAL(ReturnPressed()),
            this, SLOT(ReturnPressed()));
    connect(lineForTypeText, SIGNAL(ReturnPressed()),
            this, SLOT(ReturnPressed()));
    connect(&userclient, SIGNAL(NewMessage(QString,QString)),
            this, SLOT(AppendMessage(QString,QString)));
    connect(&userclient, SIGNAL(UserIsJoined(QString)),
            this, SLOT(UserIsJoined(QString)));
    connect(&userclient, SIGNAL(UserIsLeft(QString)),
            this, SLOT(UserIsLeft(QString)));
    connect(    , SIGNAL(SingalFAQ()),
             this, SLOT(SlotsFAQ()));

    whoami = userclient.NickName();
    UserIsJoined(whoami);
    tableFormat.setBorder(0);
    QTimer::singleShot(10 * 1000, this, SLOT(showInformation()));
}

void Freechat::AppendMessage(const QString &from, const QString &message)
{
    if (from.isEmpty() || message.isEmpty())
        return;

    QTextCursor cursor(textFieldForViewMessages->textCursor());
    cursor.movePosition(QTextCursor::End);
    QTextTable *table = cursor.insertTable(1, 2, tableFormat);
    table->cellAt(0, 0).firstCursorPosition().insertText('<' + from + "> ");
    table->cellAt(0, 1).firstCursorPosition().insertText(message);
    QScrollBar *bar = textFieldForViewMessages->verticalScrollBar();
    bar->setValue(bar->maximum());
}

void Freechat::ReturnPressed()
{
    QString text = lineForTypeText->text();
    if (text.isEmpty())
    {
        return;
    }
    else
    {
        /*clear code*/
    }

    if (text.startsWith(QChar('/')))
    {
        QColor color = textFieldForViewMessages->textColor();
        textFieldForViewMessages->setTextColor(black);
        textFieldForViewMessages->append(tr("! Unknown command: %1")
                         .arg(text.left(text.indexOf(' '))));
        textFieldForViewMessages->setTextColor(color);
    }
    else
    {
        userclient.SendMessage(text);
        AppendMessage(whoami, text);
    }

    lineForTypeText->clear();
}

void Freechat::UserIsJoined(const QString &nick)
{
    if (nick.isEmpty())
    {
        return;
    }
    else
    {
        /*clear code*/
    }

    QColor color = textFieldForViewMessages->textColor();
    textFieldForViewMessages->setTextColor(gray);
    textFieldForViewMessages->append(tr("* %1 has joined").arg(nick));
    textFieldForViewMessages->setTextColor(color);
    listWithNicknameOfUser->addItem(nick);
}

void Freechat::UserIsLeft(const QString &nick)
{
    if (nick.isEmpty())
    {
        return;
    }
    else
    {
        /*clear code*/
    }

    QList<QListWidgetItem *> items = listWithNicknameOfUser->findItems(nick, MatchExactly);
    if (items.isEmpty())
    {
        return;
    }
    else
    {
        /*clear code*/
    }

    delete items.at(0);
    QColor color = textFieldForViewMessages->textColor();
    textFieldForViewMessages->setTextColor(gray);
    textFieldForViewMessages->append(tr("* %1 has left").arg(nick));
    textFieldForViewMessages->setTextColor(color);
}

void Freechat::HiiiiiiBoy()
{
    if (listWithNicknameOfUser->count() == 1)
    {
        QMessageBox::information(this, tr("Freechat"),
        tr("Let's try the best!"));
    }
    else
    {
        /*clear code*/
    }
}

void Freechat::SlotsFAQ()
{
    if (listWithNicknameOfUser->count() == 1)
    {
        QMessageBox::information(this, tr("FAQ"),
        tr("What about this program?!", "Something text"));
    }
    else
    {
        /*clear code*/
    }
}
