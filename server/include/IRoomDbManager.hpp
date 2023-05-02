#pragma once

#include "IDbManager.hpp"

class IRoomDbManager
{
public:
    virtual void insertRoom(const std::string&) = 0; // Предполагается, что будет передан JSON с описанием комнаты

    virtual void insertNewMessage(const std::string&) = 0; // Предполагается, что будет передан JSON с ID комнаты + сообщение

    virtual std::string getNewMessage(const std::string& roomId) = 0;

    virtual void deleteRoom(const std::string&) = 0;
};