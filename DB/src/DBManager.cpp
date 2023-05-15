#include "DBManager.hpp"

const std::string CONNECTION_FAILED_ERROR = "Can't connect to database";

DBManager::DBManager() {
    db = QSqlDatabase::addDatabase(DBType, connectionName);
    connect(); //???
}

 void DBManager::connect() {
    db.setHostName    (hostName);
    db.setPort        (port);
    db.setDatabaseName(DBName);
    db.setUserName    (username);
    db.setPassword    (password);
    if(!db.open())
        isConnected = false;
    else 
        isConnected = true;
}

QSqlQuery DBManager::execute(const QString& queryStr) {
    if(!isConnected) throw std::runtime_error(CONNECTION_FAILED_ERROR);
    QSqlQuery query(db);
    if(!query.exec(queryStr))
        throw(std::runtime_error(query.lastError().text().toStdString()));
    query.first();
    return query;
}
