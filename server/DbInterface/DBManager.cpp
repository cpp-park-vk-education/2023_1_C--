#include "DBManager.hpp"

DbManager::DbManager(QSettings* settings)
{
    db = QSqlDatabase::addDatabase(
        settings->value("DBType").toString(),
        settings->value("connectionName").toString()
    );

    this->settings = settings;

    connect();
}

void DbManager::connect()
{
    db.setHostName(settings->value("hostname").toString());

    db.setPort(settings->value("port").toInt());

    db.setDatabaseName(settings->value("dbname").toString());

    db.setUserName(settings->value("username").toString());

    db.setPassword(settings->value("password").toString());

    if(!db.open())
        qDebug() << db.lastError().text();
}

QSqlQuery DbManager::exec(const std::string& queryStr)
{
    QSqlQuery query(db);

    if (!query.exec(QString::fromStdString(queryStr)))
    {
        
    }
    else return query;
}