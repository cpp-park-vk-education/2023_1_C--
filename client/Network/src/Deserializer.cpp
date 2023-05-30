#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <optional>
#include "Deserializer.hpp"
#include "SerializationKeys.hpp"

static QJsonObject ByteArrayToJsonObj(std::vector<char> byteArray) {
    QByteArray qByteArray;
    for (auto byte: byteArray)
        qByteArray.push_back(byte);
    return QJsonDocument::fromJson(qByteArray).object();
}

static std::optional<Message> DeserializeMessageInternal(const QJsonObject& messageJsonObj) {
    Message message;
    const auto temp = messageJsonObj[AUTHOR_KEY].toString().toStdString();
    if (temp.empty())
        return std::nullopt;
    message.author = temp;
    message.id = messageJsonObj[ID_KEY].toInt();
    message.content = messageJsonObj[CONTENT_KEY].toString().toStdString();
    message.sendingData = messageJsonObj[SENDING_DATA_KEY].toString().toStdString();
    return message;
}

static UserInfo DeserializeUserInfoInternal(const QJsonObject& infoJsonObj) {
    UserInfo info;
    info.login = infoJsonObj[LOGIN_KEY].toString().toStdString();
    info.nickname = infoJsonObj[NICKNAME_KEY].toString().toStdString();
    info.firstName = infoJsonObj[FIRSTNAME_KEY].toString().toStdString();
    info.lastName = infoJsonObj[LASTNAME_KEY].toString().toStdString();
    return info;
}

static RoomInfo DeserializeRoomInfo(const QJsonObject& roomInfoJsonObj) {
    RoomInfo roomInfo;
    roomInfo.id = roomInfoJsonObj[ID_KEY].toInt();
    roomInfo.name = roomInfoJsonObj[NAME_KEY].toString().toStdString();
    auto membersJsonArr = roomInfoJsonObj[MEMBERS_KEY].toArray();
    std::vector<UserInfo> members;
    for (const auto& memberValue: membersJsonArr) {
        members.push_back(
            DeserializeUserInfoInternal(memberValue.toObject())
        );
    }
    roomInfo.members = members;
    return roomInfo;
}

static std::vector<Message> DeserializeVectorOfMessages(const QJsonArray& messagesJsonArr) {
    std::vector<Message> messages;
    for (const auto& messageValue: messagesJsonArr) {
        auto messageObj = messageValue.toObject();
        auto message = DeserializeMessageInternal(messageObj[MESSAGE_KEY].toObject());
        if (message)
            messages.push_back(message.value());
    }
    return messages;
}

static std::vector<RoomInfo> DeserializeVectorOfRooms(const QJsonArray& roomsJsonArr) {
    std::vector<RoomInfo> rooms;
    for (const auto& roomValue: roomsJsonArr) {
        auto roomJsonObj = roomValue.toObject();
        auto roomInfo = DeserializeRoomInfo(roomJsonObj[ROOM_INFO_KEY].toObject());
        rooms.push_back(roomInfo);
    }
    return rooms;
}

UserData Deserializer::DeserializeUserData(std::vector<char> byteArray) {
    UserData data;
    auto jsonObj = ByteArrayToJsonObj(byteArray);
    data.info = DeserializeUserInfoInternal(jsonObj[USER_INFO_KEY].toObject());
    data.rooms = DeserializeVectorOfRooms(jsonObj[ROOMS_KEY].toArray());
    return data;    
}

RoomInfo Deserializer::DeserializeCreateRoomResponse(std::vector<char> byteArray) {
    RoomInfo data;
    auto jsonObj = ByteArrayToJsonObj(byteArray);
    return DeserializeRoomInfo(jsonObj);
}

Message Deserializer::DeserializeMessage(std::vector<char> byteArray) {
    auto responseJsonObj = ByteArrayToJsonObj(byteArray);
    auto message = DeserializeMessageInternal(
        responseJsonObj[MESSAGE_KEY].toObject()
    );
    if (message)
        return message.value();
    else
        return Message{};
}

std::vector<Message> Deserializer::DeserializeRoomMessages(std::vector<char> byteArray) {
    auto jsonObj = ByteArrayToJsonObj(byteArray);
    auto debugData = QJsonDocument(jsonObj).toJson(QJsonDocument::Compact).toStdString();
    auto messageJsonArr = jsonObj[MESSAGES_KEY].toArray();
    return DeserializeVectorOfMessages(messageJsonArr);
}

UserInfo Deserializer::DeserializeUserInfo(std::vector<char> byteArray) {
    auto userInfoJsonValue = ByteArrayToJsonObj(byteArray);
    auto userInfoJsonObj = userInfoJsonValue[USER_INFO_KEY].toObject();
    return DeserializeUserInfoInternal(userInfoJsonObj);
}