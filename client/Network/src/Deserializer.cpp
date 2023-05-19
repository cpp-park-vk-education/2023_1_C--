#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include "Deserializer.hpp"
#include "SerializationKeys.hpp"

static QJsonObject ByteArrayToJsonObj(std::vector<char> byteArray) {
    QByteArray qByteArray;
    for (auto byte: byteArray)
        qByteArray.push_back(byte);
    return QJsonDocument::fromJson(qByteArray).object();
}

static Message DeserializeMessageInternal(const QJsonObject& messageJsonObj) {
    Message message;
    message.id = messageJsonObj[ID_KEY].toInt();
    message.content = messageJsonObj[CONTENT_KEY].toString().toStdString();
    message.author = messageJsonObj[AUTHOR_KEY].toString().toStdString();
    message.sendingData = messageJsonObj[SENDING_DATA_KEY].toString().toStdString();
    return message;
}

static RoomInfo DeserializeRoomInfo(const QJsonObject& roomInfoJsonObj) {
    RoomInfo roomInfo;
    roomInfo.id = roomInfoJsonObj[ID_KEY].toInt();
    roomInfo.name = roomInfoJsonObj[NAME_KEY].toString().toStdString();
    auto membersJsonArr = roomInfoJsonObj[MEMBERS_KEY].toArray();
    std::vector<std::string> members;
    for (const auto& memberValue: membersJsonArr) {
        auto memberLogin = memberValue.toString().toStdString();
        members.push_back(memberLogin);
    }
    roomInfo.members = members;
    return roomInfo;
}

static std::vector<Message> DeserializeVectorOfMessages(const QJsonArray& messagesJsonArr) {
    std::vector<Message> messages;
    for (const auto& messageValue: messagesJsonArr) {
        auto messageObj = messageValue.toObject();
        Message message = DeserializeMessageInternal(messageObj[MESSAGE_KEY].toObject());
        messages.push_back(message);
    }
    return messages;
}

static std::vector<RoomInfo> DeserializeVectorOfRooms(const QJsonArray& roomsJsonArr) {
    std::vector<RoomInfo> rooms;
    auto debugData = QJsonDocument(roomsJsonArr).toJson(QJsonDocument::Compact).toStdString();
    for (const auto& roomValue: roomsJsonArr) {
        auto roomJsonObj = roomValue.toObject();
        auto roomInfo = DeserializeRoomInfo(roomJsonObj[ROOM_INFO_KEY].toObject());
        rooms.push_back(roomInfo);
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

UserData Deserializer::DeserializeUserData(std::vector<char> byteArray) {
    UserData data;
    auto jsonObj = ByteArrayToJsonObj(byteArray);
    data.info = DeserializeUserInfo(jsonObj[USER_INFO_KEY].toObject());
    data.rooms = DeserializeVectorOfRooms(jsonObj[ROOMS_KEY].toArray());
    return data;    
}

RoomInfo Deserializer::DeserializeCreateRoomResponse(std::vector<char> byteArray) {
    RoomInfo data;
    auto jsonObj = ByteArrayToJsonObj(byteArray);
    return DeserializeRoomInfo(jsonObj);
}

Message Deserializer::DeserializeMessage(std::vector<char> byteArray) {
    return DeserializeMessageInternal(ByteArrayToJsonObj(byteArray));
}

std::vector<Message> Deserializer::DeserializeRoomMessages(std::vector<char> byteArray) {
    auto jsonObj = ByteArrayToJsonObj(byteArray);
    auto debugData = QJsonDocument(jsonObj).toJson(QJsonDocument::Compact).toStdString();
    auto messageJsonArr = jsonObj[MESSAGES_KEY].toArray();
    return DeserializeVectorOfMessages(messageJsonArr);
}

