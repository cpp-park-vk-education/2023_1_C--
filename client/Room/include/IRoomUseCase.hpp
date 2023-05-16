#pragma once
#include <memory>
#include "RoomData.hpp"

class IRoomUseCase {
public:
    virtual ~IRoomUseCase() {}
    virtual void CreateRoom(const RoomInfo& roomInfo) = 0;
    virtual void SendMessage(const Message& message) = 0;
    virtual void GetNewMessage(const int roomID) = 0;
    virtual void GetRoomMessage(const int roomID) = 0;
};

using IRoomUseCaseSPtr = std::shared_ptr<IRoomUseCase>;
