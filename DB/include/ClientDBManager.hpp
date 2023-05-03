#pragma once

#include "IClientDBManager.hpp"

class ClientDBManager: public IClientDBManager {
public:
    ClientDBManager();

    Client getClient(const std::string& login)                                    override;

    int changeLogin(const std::string& old_login, const std::string& new_login)   override;

    int changePassword(const std::string& login, const std::string& new_password) override;

    int setFirstname(const std::string& login, const std::string& firstname)      override;

    int setLastname(const std::string& login, const std::string& lastname)        override;

};

