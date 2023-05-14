#include "SendMessageService.hpp"

void SendMessageService::SendMessage(const int id, const std::string& username, const std::string& message)
{
    roomManager->insertNewMessage(id, QString::fromStdString(username), QString::fromStdString(message));
}