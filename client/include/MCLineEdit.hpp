#pragma once

#include <QLineEdit>
#include <QCompleter>

class MCLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit MCLineEdit(QWidget *parent = 0);
    void setMultipleCompleter(QCompleter*);

protected:
    void keyPressEvent(QKeyEvent *e);

private:
    QString cursorWord(const QString& sentence) const;

private slots:
    void insertCompletion(QString);

private:
    QCompleter* c;
};
