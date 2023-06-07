#pragma once
#include <memory>
#include "UserData.hpp"
#include "Message.hpp"

class IRoomUseCase {
public:
    virtual ~IRoomUseCase() {}
    virtual void CreateRoom(std::string&& name,
                            std::vector<std::string>&& members) = 0;
    virtual void SendMessage(Message&& message) = 0;
    // virtual void GetNewMessage(const int roomID) = 0;
    virtual void GetRoomMessages(const int roomID) = 0;
    virtual void RefreshMainPage() = 0;
    virtual void AddUser(const int roomID, const std::string& login) = 0;
    virtual void ShowMainPage() = 0;
    virtual void ShowMainPage(UserData&& userData) = 0;
};

using IRoomUseCaseSPtr = std::shared_ptr<IRoomUseCase>;
