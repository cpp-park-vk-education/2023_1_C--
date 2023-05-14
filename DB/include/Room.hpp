#pragma once

#include <QSqlQuery>
#include <QVariant>

struct Room {
    int ID;
    QString name;

    explicit Room(const QSqlQuery&);
};
