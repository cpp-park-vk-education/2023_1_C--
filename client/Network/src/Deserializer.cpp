#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include "Deserializer.hpp"
#include "SerializationKeys.hpp"

#include <QFile>

static UserInfo DeserializeUserInfo(const QJsonObject& infoJsonObj) {
    UserInfo info;
    info.login = infoJsonObj[LOGIN_KEY].toString().toStdString();
    info.nickname = infoJsonObj[NICKNAME_KEY].toString().toStdString();
    info.firstName = infoJsonObj[FIRSTNAME_KEY].toString().toStdString();
    info.lastName = infoJsonObj[LASTNAME_KEY].toString().toStdString();
    return info;
}

static Message DeserializeMessage(const QJsonObject& messageJsonObj) {
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
        Message message = DeserializeMessage(messageValue.toObject());
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

static QJsonObject ByteArrayToJsonObj(std::vector<char> byteArray) {
    QByteArray qByteArray;
    for (auto byte: byteArray)
        qByteArray.push_back(byte);
        qDebug() << "Response data";
        qDebug() << QJsonDocument::fromJson(qByteArray).toJson(QJsonDocument::Compact).toStdString(); 
    return QJsonDocument::fromJson(qByteArray).object();
}

static void DebugPrintUserData(const UserData& data) {
    qDebug() << "After deserialization";
    qDebug() << "UserInfo";
    qDebug() << "  " <<data.info.login;
    qDebug() << "  " <<data.info.firstName;
    qDebug() << "  " <<data.info.lastName;
    qDebug() << "  " <<data.info.nickname;
    qDebug() << "VectorOfRooms";
    for (auto it = data.rooms.begin(); it != data.rooms.end(); ++it) {
        qDebug() << "  "<< "RoomInfo";
        qDebug() << "   " << it->info.id;
        qDebug() << "   " << it->info.name;
        qDebug() << "   " << it->info.members.back();
    }   
}

static QJsonObject StubJsonObj() {
    QFile file;
    file.setFileName("/home/oleg/vk-education/cpp-course/2023_1_C--/Common/LoginResponse.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray byteArray = file.readAll();
    file.close();
    qDebug() << QJsonDocument::fromJson(byteArray).toJson(QJsonDocument::Compact).toStdString();
    return QJsonDocument::fromJson(byteArray).object();
}

UserData Deserializer::DeserializeLoginResponse(std::vector<char> byteArray) {
    UserData data;
    // auto jsonObj = ByteArrayToJsonObj(byteArray);
    auto jsonObj = StubJsonObj();
    auto info = DeserializeUserInfo(jsonObj[USER_INFO_KEY].toObject());
    auto rooms = DeserializeVectorOfRooms(jsonObj[ROOMS_KEY].toArray());
    data.info = info;
    data.rooms = rooms;
    DebugPrintUserData(data);
    return data;    
}

RoomData Deserializer::DeserializeCreateRoomResponse(std::vector<char> byteArray) {
    RoomData data;
    auto jsonObj = ByteArrayToJsonObj(byteArray);
    auto info = DeserializeRoomInfo(jsonObj);
    data.info = info;
    return data;    
}

// RoomData Deserializer::DeserializeRoom(std::vector<char> byteArray) {}
