#include "ClientDBManager.hpp"

ClientDBManager::ClientDBManager() {}
Client ClientDBManager::getClient(const std::string& login)                                       {}
int    ClientDBManager::changeLogin(const std::string& old_login, const std::string& new_login)   {}
int    ClientDBManager::changePassword(const std::string& login, const std::string& new_password) {}
int    ClientDBManager::setFirstname(const std::string& login, const std::string& firstname)      {}
int    ClientDBManager::setLastname(const std::string& login, const std::string& lastname)        {}
