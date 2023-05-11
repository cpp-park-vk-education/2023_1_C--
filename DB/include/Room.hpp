#pragma once

#include <QSqlQuery>

struct Room {
    int ID;
    QString name;

    explicit Room(const QSqlQuery&);
};
