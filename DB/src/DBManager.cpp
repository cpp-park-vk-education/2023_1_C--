#include "DBManager.hpp"

DBManager::DBManager() {
    db = QSqlDatabase::addDatabase(DBType, connectionName);
    connect();
}

void DBManager::connect() {
    db.setHostName    (hostName);
    db.setPort        (port);
    db.setDatabaseName(DBName);
    db.setUserName    (username);
    db.setPassword    (password);
    if(!db.open())
        connected = false;
    else 
        connected = true;
}

QSqlQuery DBManager::execute(const QString& queryStr) {
    QSqlQuery query(db);
    if(!query.exec(queryStr))
        throw(std::runtime_error("Query isn't correct!"));
    query.first();
    return query;
}

bool DBManager::isConnected() {
    return connected;
}