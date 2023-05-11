#pragma once

#include <qt5/QtCore/QSettings>
#include <qt5/QtSql/QSqlDatabase>
#include <qt5/QtSql/QSqlError>
#include <qt5/QtSql/QSqlQuery>
#include <qt5/QtCore/QDebug>

#include "IDBManager.hpp"

class DbManager : IDBManager
{
public:
    DbManager(QSettings* settings);

    void connect() override;

    QSqlQuery exec(const std::string&);
private:
    QSettings* settings;

    QSqlDatabase db;
};