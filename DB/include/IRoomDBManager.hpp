#pragma once

#include <string>
#include "Message.hpp"
#include "Room.hpp"

class IRoomDBManager {
public:
    virtual QVector<Room> getRooms(const QString&) = 0;

    virtual QVector<Message> getMessages(const int) = 0;

    virtual Room getRoom(const int room_ID) = 0;

    virtual Room insertRoom(const QString&, const QString&) = 0;

    virtual Message insertNewMessage(const int room_ID, const QString& username, const QString& text) = 0;

    virtual Message getNewMessage(const int room_ID) = 0;

    virtual void deleteRoom(const int room_ID) = 0;

    virtual Room renameRoom(const int room_ID, const QString& new_name) = 0;

    virtual void addClientToRoom(const int room_ID, const QString& login) = 0;

    virtual void deleteClientFromRoom(const int room_ID, const QString& login) = 0;

    virtual Message changeMessageContext(const int message_ID, const QString& new_context) = 0;

};
