#pragma once
#include <string>

struct Message {
    Message() {}
    ~Message() {}

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

    int id;
    int roomID;
    std::string content;
    std::string author;
    std::string sendingData;
};
