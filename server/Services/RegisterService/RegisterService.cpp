#include "RegisterService.hpp"

Client RegisterService::regClient(const std::string& login, const std::string& password, const std::string& username)
{
    auto hashPassword = QCryptographicHash::hash(QByteArray::fromStdString(password), QCryptographicHash::Algorithm::Sha256);

    return clientManager->createClient(
        QString::fromStdString(login), hashPassword, QString::fromStdString(username)
    );
}