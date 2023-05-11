#pragma once

#include <string>

struct Client{};

class IClientDBManager {
public:
    virtual Client getClient(const std::string& login) = 0;

    virtual int changeLogin(const std::string& old_login, const std::string& new_login) = 0;

    virtual int changePassword(const std::string& login, const std::string& new_password) = 0;

    virtual int setFirstname(const std::string& login, const std::string& firstname) = 0;

    virtual int setLastname(const std::string& login, const std::string& lastname) = 0;

};