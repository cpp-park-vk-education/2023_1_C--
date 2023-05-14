#pragma once

#include "IClientDBManager.hpp"
#include "DBManager.hpp"
#include "Client.hpp"
#include <memory>

class ClientDBManager: public IClientDBManager {
public:
    ClientDBManager(std::shared_ptr<DBManager>&);

    Client getClient(const QString& login) override;

    Client createClient(const QString&, const QString&, const QString&) override;

    Client changeLogin(const QString& old_login, const QString& new_login) override;

    Client changePassword(const QString& login, const QString& new_password) override;

    Client setFirstname(const QString& login, const QString& firstname) override;

    Client setLastname(const QString& login, const QString& lastname) override;

    QVector<Client> getClientsInRoom(const int roomID) override;

private:
    std::shared_ptr<DBManager> dbManager;
};

