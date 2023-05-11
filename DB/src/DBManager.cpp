#include "DBManager.hpp"

DBManager::DBManager() {
    db = QSqlDatabase::addDatabase(DBType, connectionName);
    connect();
}

int DBManager::connect() {
    db.setHostName    (hostName);
    db.setPort        (port);
    db.setDatabaseName(DBName);
    db.setUserName    (username);
    db.setPassword    (password);
    if(!db.open())
        qDebug() << db.lastError().text();
}

QSqlQuery DBManager::execute(const QString& queryStr) {
    QSqlQuery query(db);
    if(!query.exec(queryStr))
        qDebug() << db.lastError().text();
    else
        return query;
}
