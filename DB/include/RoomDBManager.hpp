#pragma once

#include "IRoomDBManager.hpp"
#include "DBManager.hpp"
#include "Client.hpp"
#include <memory>

class RoomDBManager: public IRoomDBManager {
public:
    RoomDBManager(std::shared_ptr<DBManager>&);

    QVector<Room> getRooms(const QString&) override;

    QVector<Message> getMessages(const int) override;

    Room insertRoom(const QString& username, const QString& roomname) override;

    Message insertNewMessage(const int room_ID, const QString& username, const QString& text) override;

    void deleteRoom(const int room_ID) override;

    Room renameRoom(const int room_ID, const QString& new_name) override;

    void addClientToRoom(const int room_ID, const QString& username) override;

    void deleteClientFromRoom(const int room_ID, const QString& username) override;

    Message changeMessageContext(const int message_ID, const QString& new_context) override;

private:
    std::shared_ptr<DBManager> dbManager;
    
    Room getRoom(const int room_ID) override;

    Message getNewMessage(const int room_ID) override;

    Message getMessage(const int);

};

