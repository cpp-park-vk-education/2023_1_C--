#include "RoomDBManager.hpp"

RoomDBManager::RoomDBManager(){}
Room    RoomDBManager::getRoom(const int room_ID)                                                                   {}
int     RoomDBManager::insertRoom(const std::string& name)                                                          {}
int     RoomDBManager::insertNewMessage(const int room_ID, const std::string& text)                                 {}
Message RoomDBManager::getNewMessage(const int room_ID)                                                             {}
int     RoomDBManager::deleteRoom(const int room_ID)                                                                {}
int     RoomDBManager::renameRoom(const int room_ID, const std::string& new_name)                                   {}
int     RoomDBManager::addClientToRoom(const int room_ID, const std::string& login)                                 {}
int     RoomDBManager::deleteClientFromRoom(const int room_ID, const std::string& login)                            {}
int     RoomDBManager::changeMessageContext(const int room_ID, const int message_ID, const std::string& new_context){}
