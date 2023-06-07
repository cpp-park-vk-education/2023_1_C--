#pragma once

#include <QSqlQuery>
#include <QVariant>

struct Client
{
    explicit Client(const QSqlQuery&);

    Client() = default;

    QString login;
    QString password;
    QString username;
    QString firstName;
    QString lastName;
};
