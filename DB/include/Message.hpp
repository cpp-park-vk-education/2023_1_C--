#pragma once

#include <QSqlQuery>
#include <QDateTime>
#include <QVariant>

struct Message
{
    int ID;
    int roomID;
    QString user;
    QString context;
    QDateTime date;

    Message() = default;

    explicit Message(const QSqlQuery&);
};
