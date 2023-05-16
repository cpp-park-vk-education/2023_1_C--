#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include "Deserializer.hpp"
#include "SerializationKeys.hpp"

#include <QFile>

static QJsonObject ByteArrayToJsonObj(std::vector<char> byteArray) {
    QByteArray qByteArray;
    for (auto byte: byteArray)
        qByteArray.push_back(byte);
    return QJsonDocument::fromJson(qByteArray).object();
}

static Message DeserializeMessageInternal(const QJsonObject& messageJsonObj) {
    Message message;
    message.id = messageJsonObj[ID_KEY].toString().toInt();
    message.content = messageJsonObj[CONTENT_KEY].toString().toStdString();
    message.author = messageJsonObj[AUTHOR_KEY].toString().toStdString();
    message.sendingData = messageJsonObj[SENDING_DATA_KEY].toString().toStdString();
    return message;
}

static RoomInfo DeserializeRoomInfo(const QJsonObject& roomInfoJsonObj) {
    RoomInfo roomInfo;
    roomInfo.id = roomInfoJsonObj[ID_KEY].toString().toInt();
    roomInfo.name = roomInfoJsonObj[NAME_KEY].toString().toStdString();
    auto membersJsonArr = roomInfoJsonObj[MEMBERS_KEY].toArray();
    std::vector<std::string> members;
    for (const QJsonValue& memberValue: membersJsonArr) {
        auto memberLogin = memberValue.toString().toStdString();
        members.push_back(memberLogin);
    }
    roomInfo.members = members;
    return roomInfo;
}

static std::vector<Message> DeserializeVectorOfMessages(const QJsonArray& messagesJsonArr) {
    std::vector<Message> messages;
    for (const QJsonValue& messageValue: messagesJsonArr) {
        Message message = DeserializeMessageInternal(messageValue.toObject());
        messages.push_back(message);
    }
    return messages;
}

static std::vector<RoomData> DeserializeVectorOfRooms(const QJsonArray& roomsJsonArr) {
    std::vector<RoomData> rooms;
    for (const QJsonValue& roomValue: roomsJsonArr) {
        auto roomJsonObj = roomValue.toObject();
        auto roomInfo = DeserializeRoomInfo(roomJsonObj[ROOM_INFO_KEY].toObject());
        RoomData room;
        room.info = roomInfo;
        rooms.push_back(room);
    }
    return rooms;

}

static UserInfo DeserializeUserInfo(const QJsonObject& infoJsonObj) {
    UserInfo info;
    info.login = infoJsonObj[LOGIN_KEY].toString().toStdString();
    info.nickname = infoJsonObj[NICKNAME_KEY].toString().toStdString();
    info.firstName = infoJsonObj[FIRSTNAME_KEY].toString().toStdString();
    info.lastName = infoJsonObj[LASTNAME_KEY].toString().toStdString();
    return info;
}

UserData Deserializer::DeserializeRoomData(std::vector<char> byteArray) {
    UserData data;
    auto jsonObj = ByteArrayToJsonObj(byteArray);
    data.info = DeserializeUserInfo(jsonObj[USER_INFO_KEY].toObject());
    data.rooms = DeserializeVectorOfRooms(jsonObj[ROOMS_KEY].toArray());
    return data;    
}

RoomData Deserializer::DeserializeCreateRoomResponse(std::vector<char> byteArray) {
    RoomData data;
    auto jsonObj = ByteArrayToJsonObj(byteArray);
    auto info = DeserializeRoomInfo(jsonObj);
    data.info = info;
    return data;    
}

Message Deserializer::DeserializeMessage(std::vector<char> byteArray) {
    return DeserializeMessageInternal(ByteArrayToJsonObj(byteArray));
}

std::vector<Message> Deserializer::DeserializeRoomMessages(std::vector<char> byteArray) {
    auto jsonObj = ByteArrayToJsonObj(byteArray);
    auto messageJsonArr = jsonObj[MESSAGES_KEY].toArray();
    return DeserializeVectorOfMessages(messageJsonArr);
}

