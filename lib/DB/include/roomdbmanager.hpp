#pragma once

#include "IRoomDBManager.hpp"

class RoomDBManager: public IRoomDBManager {
public:
    RoomDBManager();
    Room getRoom(const int room_ID)                                                                   override;
    int insertRoom(const std::string& name)                                                           override;
    int insertNewMessage(const int room_ID, const std::string& text)                                  override;
    Message getNewMessage(const int room_ID)                                                          override;
    int deleteRoom(const int room_ID)                                                                 override;
    int renameRoom(const int room_ID, const std::string& new_name)                                    override;
    int addClientToRoom(const int room_ID, const std::string& login)                                  override;
    int deleteClientFromRoom(const int room_ID, const std::string& login)                             override;
    int changeMessageContext(const int room_ID, const int message_ID, const std::string& new_context) override;
};

