#pragma once

#include "Client.hpp"

class IClientDBManager {
public:
    virtual Client getClient(const QString& login) = 0;

    virtual Client createClient(const QString&, const QString&, const QString&) = 0;

    virtual Client changeLogin(const QString& old_login, const QString& new_login) = 0;

    virtual Client changePassword(const QString& login, const QString& new_password) = 0;

    virtual Client setFirstname(const QString& login, const QString& firstname) = 0;

    virtual Client setLastname(const QString& login, const QString& lastname) = 0;

    virtual QVector<Client> getClientsInRoom(const int roomID) = 0;

};
