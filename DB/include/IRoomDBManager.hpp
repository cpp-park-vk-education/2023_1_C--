#pragma once

#include <string>

struct Room{};
struct Message{};

class IRoomDBManager {
public:
    virtual Room getRoom(const int room_ID) = 0;

    virtual int insertRoom(const std::string& name) = 0;

    virtual int insertNewMessage(const int room_ID, const std::string& text) = 0;

    virtual Message getNewMessage(const int room_ID) = 0;

    virtual int deleteRoom(const int room_ID) = 0;

    virtual int renameRoom(const int room_ID, const std::string& new_name) = 0;

    virtual int addClientToRoom(const int room_ID, const std::string& login) = 0;

    virtual int deleteClientFromRoom(const int room_ID, const std::string& login) = 0;

    virtual int changeMessageContext(const int room_ID, const int message_ID, const std::string& new_context) = 0;
};
