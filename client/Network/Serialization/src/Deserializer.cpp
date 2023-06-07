#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <optional>
#include "Deserializer.hpp"
#include "SerializationKeys.hpp"

static QJsonObject ByteArrayToJsonObj(std::vector<char> byteArray) {
    QByteArray qByteArray(byteArray.data(), byteArray.size());
    return QJsonDocument::fromJson(qByteArray).object();
}

static std::optional<Message> DeserializeMessageInternal(const QJsonObject& messageJsonObj) {
    if (messageJsonObj.isEmpty())
        return std::nullopt;
    if (messageJsonObj.value(AUTHOR_KEY).toString().isEmpty())
        return std::nullopt;
    Message message;
    message.author = messageJsonObj[AUTHOR_KEY].toString().toStdString();
    message.id = messageJsonObj[ID_KEY].toInt();
    message.content = messageJsonObj[CONTENT_KEY].toString().toStdString();
    message.sendingData = messageJsonObj[SENDING_DATA_KEY].toString().toStdString();
    return message;
}

static std::optional<UserInfo> DeserializeUserInfoInternal(const QJsonObject& infoJsonObj) {
    if (infoJsonObj.isEmpty())
        return std::nullopt;
    if (infoJsonObj.value(LOGIN_KEY).toString().isEmpty())
        return std::nullopt;
    UserInfo info;
    info.login = infoJsonObj[LOGIN_KEY].toString().toStdString();
    info.nickname = infoJsonObj[NICKNAME_KEY].toString().toStdString();
    info.firstName = infoJsonObj[FIRSTNAME_KEY].toString().toStdString();
    info.lastName = infoJsonObj[LASTNAME_KEY].toString().toStdString();
    return info;
}

static std::optional<RoomInfo> DeserializeRoomInfo(const QJsonObject& roomInfoJsonObj) {
    if (roomInfoJsonObj.isEmpty())
        return std::nullopt;
    if (!roomInfoJsonObj.value(ID_KEY).toInt())
        return std::nullopt;    
    RoomInfo roomInfo;
    roomInfo.id = roomInfoJsonObj[ID_KEY].toInt();
    roomInfo.name = roomInfoJsonObj[NAME_KEY].toString().toStdString();
    auto membersJsonArr = roomInfoJsonObj[MEMBERS_KEY].toArray();
    std::vector<UserInfo> members;
    for (const auto& memberValue: membersJsonArr) {
        auto info = DeserializeUserInfoInternal(memberValue.toObject());
        if (info)
            members.push_back(info.value());
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
        auto roomJsonObj = roomValue.toObject().value(ROOM_INFO_KEY).toObject();
        auto roomInfo = DeserializeRoomInfo(roomJsonObj);
        if (roomInfo)
            rooms.push_back(roomInfo.value());
    }
    return rooms;
}

UserData Deserializer::DeserializeUserData(const std::vector<char>& byteArray) {
    UserData data;
    auto jsonObj = ByteArrayToJsonObj(byteArray);
    auto info = DeserializeUserInfoInternal(jsonObj[USER_INFO_KEY].toObject());
    if (info)
        data.info = info.value();
    data.rooms = DeserializeVectorOfRooms(jsonObj[ROOMS_KEY].toArray());
    return data;    
}

RoomInfo Deserializer::DeserializeCreateRoomResponse(const std::vector<char>& byteArray) {
    RoomInfo roomInfo_;
    auto jsonObj = ByteArrayToJsonObj(byteArray);
    auto roomInfo = DeserializeRoomInfo(jsonObj);
    if (roomInfo)
        roomInfo_ = roomInfo.value();
    return roomInfo_;
}

Message Deserializer::DeserializeMessage(const std::vector<char>& byteArray) {
    Message message_;
    auto responseJsonObj = ByteArrayToJsonObj(byteArray);
    auto message = DeserializeMessageInternal(responseJsonObj[MESSAGE_KEY].toObject());
    if (message)
        message_ = message.value();
    return message_;
}

std::vector<Message> Deserializer::DeserializeRoomMessages(const std::vector<char>& byteArray) {
    auto jsonObj = ByteArrayToJsonObj(byteArray);
    return DeserializeVectorOfMessages(jsonObj.value(MESSAGES_KEY).toArray());
}

UserInfo Deserializer::DeserializeUserInfo(const std::vector<char>& byteArray) {
    UserInfo info_;
    auto userInfoJsonObj = ByteArrayToJsonObj(byteArray);
    auto info = DeserializeUserInfoInternal(userInfoJsonObj[USER_INFO_KEY].toObject());
    if (info)
        info_ = info.value();
    return info_;
}
