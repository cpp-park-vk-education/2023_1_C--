#include "ClientDBManager.hpp"

const std::string NO_SUCH_USER_ERROR = "There is no such user!";
const std::string SMTH_WENT_WRONG_ERROR = "Something went wrong!";

ClientDBManager::ClientDBManager(std::shared_ptr<DBManager>& manager) {
    dbManager = manager;
}

Client ClientDBManager::getClient(const QString& login) {
    const QString queryStr = "SELECT * FROM users WHERE login = '" + login + "'";
    QSqlQuery query;
    try {
        query = dbManager->execute(queryStr);
    } catch (const std::runtime_error& err) {
        throw std::runtime_error(NO_SUCH_USER_ERROR);
    }
    Client client = Client(query);
    return client;
}

Client ClientDBManager::createClient(const QString& login, const QString& password, const QString& username) {
    const QString queryStr = "INSERT INTO users VALUES ('" + login +
            "', '" + password + "', '" + username + "');";
    try {
        dbManager->execute(queryStr);
    } catch (const std::runtime_error& err) {
        throw std::runtime_error(SMTH_WENT_WRONG_ERROR);
    }
    return getClient(username);
}

Client ClientDBManager::changeLogin(const QString& old_login, const QString& new_login) {
    const QString queryStr="UPDATE users "
            "SET login = '" + new_login + ""
            "'WHERE login = '" + old_login + "'";
    try { 
        dbManager->execute(queryStr);
    } catch (const std::runtime_error& err) {
        throw std::runtime_error(SMTH_WENT_WRONG_ERROR);
    }
    return getClient(new_login);
}

Client ClientDBManager::changePassword(const QString& login, const QString& new_password) {
    const QString queryStr= "UPDATE users "
            "SET password = '" + new_password + ""
            "'WHERE login = '" + login + "'";
    try {
        dbManager->execute(queryStr);
    } catch (const std::runtime_error& err) {
        throw std::runtime_error(SMTH_WENT_WRONG_ERROR);
    }
    return getClient(login);
}

Client ClientDBManager::setFirstname(const QString& login, const QString& firstname) {
    const QString queryStr="UPDATE users "
            "SET firstname = '" + firstname + ""
            "'WHERE login = '" + login + "'";
    try {
        dbManager->execute(queryStr);
    } catch (const std::runtime_error& err) {
        throw std::runtime_error(SMTH_WENT_WRONG_ERROR);
    }
    return getClient(login);
}

Client ClientDBManager::setLastname(const QString& login, const QString& lastname) {
    const QString queryStr="UPDATE users "
            "SET lastname = '" + lastname + ""
            "'WHERE login = '" + login + "'";
    try {
        dbManager->execute(queryStr);
    } catch (const std::runtime_error& err) {
        throw std::runtime_error(SMTH_WENT_WRONG_ERROR);
    }
    return getClient(login);
}

QVector<Client> ClientDBManager::getClientsInRoom(const int roomID) {
    const QString queryStr = "SELECT * FROM users_rooms "
            "WHERE room_id = " + QString::number(roomID);
    QSqlQuery query; 
    try {
        query = dbManager->execute(queryStr);
    } catch (const std::runtime_error& err) {
        throw std::runtime_error(SMTH_WENT_WRONG_ERROR);
    }
    QStringList users;
    users.push_back(query.value(1).toString());
    while(query.next()) {
        users.push_back(query.value(1).toString());
    }
    QVector<Client> clients;
    for(auto name : users) {
        clients.push_back(getClient(name));
    }
    qDebug() << clients.last().login;
    return clients;
}
