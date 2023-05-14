#pragma once

#include <QSqlQuery>
#include <QVariant>

struct Client
{
    explicit Client(const QSqlQuery&);
    QString login;
    QString password;
    QString username;
    QString firstName;
    QString lastName;
};
