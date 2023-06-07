#pragma once

#include <string>
#include <vector>
#include <QSqlQuery>

class IDBManager {
public:
    virtual void connect() = 0;

    virtual QSqlQuery execute(const QString&) = 0;
};
