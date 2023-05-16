#include "GetRoomHistoryService.hpp"

std::vector<Message> GetRoomHistoryService::getMessages(const int id)
{
   return roomManager->getMessages(id).toStdVector();
}