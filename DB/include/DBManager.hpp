#pragma once

#include "IDBManager.hpp"
#include <utility>
#include <QSqlError>
#include <QDebug>

class DBManager: public IDBManager {
public:
    DBManager();

    int connect() override;

    QSqlQuery execute(const QString&) override;

private:
    const QString DBType = "QPSQL";
    const QString connectionName = "newDataBase";

    const QString hostName = "195.19.32.74";
    const int port = 5432;
    const QString DBName = "fn1131_2022";
    const QString username = "student";
    const QString password = "bmstu";

    QSqlDatabase db;
};
