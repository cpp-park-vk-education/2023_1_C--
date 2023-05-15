#include "Deserializer.hpp"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QFile>

static UserInfo DeserializeUserInfo(const QJsonObject& infoJsonObj) {
    UserInfo info;
    info.login = infoJsonObj["login"].toString().toStdString();
    info.nickname = infoJsonObj["nickname"].toString().toStdString();
    info.firstName = infoJsonObj["firstName"].toString().toStdString();
    info.lastName = infoJsonObj["lastName"].toString().toStdString();
    return info;
}

static Message DeserializeMessage(const QJsonObject& messageJsonObj) {
    Message message;
    message.id = messageJsonObj["id"].toString().toInt();
    message.content = messageJsonObj["content"].toString().toStdString();
    message.author = messageJsonObj["author"].toString().toStdString();
    message.sendingData = messageJsonObj["sendingData"].toString().toStdString();
    return message;
}

static RoomInfo DeserializeRoomInfo(const QJsonObject& roomInfoJsonObj) {
    RoomInfo roomInfo;
    roomInfo.id = roomInfoJsonObj["id"].toString().toInt();
    roomInfo.id = roomInfoJsonObj["id"].toString().toInt();
    roomInfo.name = roomInfoJsonObj["name"].toString().toStdString();
    auto membersJsonArr = roomInfoJsonObj["members"].toArray();
    std::vector<std::string> members;
    for (const QJsonValue& memberValue: membersJsonArr) {
        auto memberLogin = memberValue.toString().toStdString();
        members.push_back(memberLogin);
    }
    roomInfo.members = std::move(members);
    return roomInfo;
}

static std::vector<RoomData> DeserializeVectorOfRooms(const QJsonArray& roomsJsonArr) {
    std::vector<RoomData> rooms;
    for (const QJsonValue& roomValue: roomsJsonArr) {
        auto roomJsonObj = roomValue.toObject();
        auto roomInfo = DeserializeRoomInfo(roomJsonObj["RoomInfo"].toObject());
        
        std::vector<Message> lastMessages;
        auto lastMessagesJsonArr = roomJsonObj["LastMessages"].toArray();            
        for (const QJsonValue& messageValue: lastMessagesJsonArr) {
            Message message = DeserializeMessage(messageValue.toObject());
            lastMessages.push_back(message);
        }

        RoomData room;
        room.info = roomInfo;
        room.lastMessages = lastMessages;
        rooms.push_back(room);
    }
    return rooms;

}

static QJsonObject ByteArrayToJsonObj(std::vector<char> byteArray) {
    QByteArray qByteArray;
    for (auto byte: byteArray)
        qByteArray.push_back(byte);
    return QJsonDocument::fromJson(qByteArray).object();
}

static QJsonObject StubJsonObj() {
    QFile file;
    file.setFileName("/home/oleg/vk-education/cpp-course/2023_1_C--/Common/StubResponse.json");
    file.setFileName("/home/oleg/vk-education/cpp-course/2023_1_C--/Common/StubResponse.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray byteArray = file.readAll();
    file.close();
    return QJsonDocument::fromJson(byteArray).object();
}

UserData Deserializer::DeserializeUserData(std::vector<char> byteArray) {
    UserData data;
    auto jsonObj = ByteArrayToJsonObj(byteArray);
    //auto jsonObj = StubJsonObj();
    auto info = DeserializeUserInfo(jsonObj["UserInfo"].toObject());
    auto rooms = DeserializeVectorOfRooms(jsonObj["VectorOfRooms"].toArray());
    data.info = info;
    data.rooms = rooms;
    return data;    
}

// RoomData Deserializer::DeserializeRoom(std::vector<char> byteArray) {}
