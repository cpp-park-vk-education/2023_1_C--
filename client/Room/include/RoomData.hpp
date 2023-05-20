#pragma once
#include <string>
#include <vector>
#include "AccountData.hpp"

struct UserInfo;

struct RoomInfo {
    int id;
    std::string name;
    std::vector<UserInfo> members;

    RoomInfo() {}

    RoomInfo(const RoomInfo& other)
        : id(other.id), name(other.name), members(other.members) {}

    RoomInfo& operator=(const RoomInfo& other) {
        id = other.id;
        name = other.name;
        members = other.members;
        return *this;
    }

    ~RoomInfo() {}
};

struct Message {
    int id;
    int roomID;
    std::string content;
    std::string author;
    std::string sendingData;

    Message() {}

    Message(const Message& other)
        : id(other.id), content(other.content),
          author(other.author), sendingData(other.sendingData) {}
           
    Message& operator=(const Message& other) {
        id = other.id;
        content = other.content;
        author = other.author;
        sendingData = other.sendingData;
        return *this;
    }
    
    ~Message() {}
};

// struct RoomData {
//     RoomInfo info;
//     std::vector<Message> lastMessages;

//     RoomData() {}

//     RoomData(const RoomData& other) 
//         : info(other.info), lastMessages(other.lastMessages) {}

//     RoomData& operator=(const RoomData& other) {
//         info = other.info;
//         lastMessages = other.lastMessages;
//         return *this;
//     }

//     ~RoomData() {}
// };
