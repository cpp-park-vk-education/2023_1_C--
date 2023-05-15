#include "GetNewMessageService.hpp"

Message GetNewMessageService::getNewMessage(const int id)
{
    return roomManager->getNewMessage(1);
}