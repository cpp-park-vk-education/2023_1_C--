#include "ClientDBManager.hpp"

ClientDBManager::ClientDBManager(std::shared_ptr<DBManager>& manager) {
    dbManager = manager;
}

Client ClientDBManager::getClient(const QString& login) {
    const QString queryStr = "SELECT * FROM users WHERE login = '" + login + "'";
    try {
        QSqlQuery query = dbManager->execute(queryStr);
    } catch (std::runtime_error& err) {
        throw std::runtime_error("There is no such user!");
    }
    Client client = Client(query);
    return client;
}

Client ClientDBManager::createClient(const QString& login, const QString& password, const QString& username) {
    const QString queryStr = "INSERT INTO users VALUES ('" + login +
            "', '" + password + "', '" + username + "');";
    dbManager->execute(queryStr);
    return getClient(username);
}

Client ClientDBManager::changeLogin(const QString& old_login, const QString& new_login) {
    const QString queryStr="UPDATE users "
            "SET login = '" + new_login + ""
            "'WHERE login = '" + old_login + "'";
    dbManager->execute(queryStr);
    return getClient(new_login);
}

Client ClientDBManager::changePassword(const QString& login, const QString& new_password) {
    const QString queryStr= "UPDATE users "
            "SET password = '" + new_password + ""
            "'WHERE login = '" + login + "'";
    dbManager->execute(queryStr);
    return getClient(login);
}

Client ClientDBManager::setFirstname(const QString& login, const QString& firstname) {
    const QString queryStr="UPDATE users "
            "SET firstname = '" + firstname + ""
            "'WHERE login = '" + login + "'";
    dbManager->execute(queryStr);
    return getClient(login);
}

Client ClientDBManager::setLastname(const QString& login, const QString& lastname) {
    const QString queryStr="UPDATE users "
            "SET lastname = '" + lastname + ""
            "'WHERE login = '" + login + "'";
    dbManager->execute(queryStr);
    return getClient(login);
}

QVector<Client> ClientDBManager::getClientsInRoom(const int roomID) {
    const QString queryStr = "SELECT * FROM users_rooms "
            "WHERE room_id = " + roomID;
    QSqlQuery query = dbManager->execute(queryStr);
    QStringList users;
    users.push_back(query.value(0).toString());
    while(query.next()) {
        users.push_back(query.value(0).toString());
    }
    QVector<Client> clients;
    for(auto name : users) {
        clients.push_back(getClient(name));
    }
    return clients;
}
