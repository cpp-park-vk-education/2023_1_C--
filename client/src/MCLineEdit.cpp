#include "MCLineEdit.hpp"
#include <QTextCursor>
#include <QAbstractItemView>
#include <QScrollBar>

MCLineEdit::MCLineEdit(QWidget *parent) :
    QLineEdit(parent)
{}

void MCLineEdit::keyPressEvent(QKeyEvent *e)
{
    QLineEdit::keyPressEvent(e);
    if (!c)
        return;

    c->setCompletionPrefix(cursorWord(this->text()));
    if (c->completionPrefix().length() < 1)
    {
        c->popup()->hide();
        return;
    }
    QRect cr = cursorRect();
    cr.setWidth(c->popup()->sizeHintForColumn(0)
                + c->popup()->verticalScrollBar()->sizeHint().width());
    c->complete(cr);
}

QString MCLineEdit::cursorWord(const QString &sentence) const
{
    return sentence.mid(sentence.left(cursorPosition()).lastIndexOf(" ") + 1,
                        cursorPosition() -
                            sentence.left(cursorPosition()).lastIndexOf(" ") - 1);
}

void MCLineEdit::insertCompletion(QString arg)
{
    setText(text().replace(text().left(cursorPosition()).lastIndexOf(" ") + 1,
                           cursorPosition() -
                               text().left(cursorPosition()).lastIndexOf(" ") - 1,
                           arg));
}

void MCLineEdit::setMultipleCompleter(QCompleter* completer)
{
    c = completer;
    c->setWidget(this);
    connect(c, SIGNAL(activated(QString)),
            this, SLOT(insertCompletion(QString)));
}
