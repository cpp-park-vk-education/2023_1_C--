#include "Deserializer.hpp"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

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
    message.id = static_cast<size_t>(messageJsonObj["id"].toInt());
    message.content = messageJsonObj["content"].toString().toStdString();
    message.author = messageJsonObj["author"].toString().toStdString();
    message.sendingData = messageJsonObj["sendingData"].toString().toStdString();
    return message;
}

static RoomInfo DeserializeRoomInfo(const QJsonObject& roomInfoJsonObj) {
    RoomInfo roomInfo;
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
        qDebug() << "   " << it->info.name;
        qDebug() << "   " << it->info.members.back();
        qDebug() << "  " << "LastMessages.back()";
        qDebug() << "   " << it->lastMessages.back().id;
        qDebug() << "   " << it->lastMessages.back().content;
        qDebug() << "   " << it->lastMessages.back().author;
        qDebug() << "   " << it->lastMessages.back().sendingData;
    }   
}

static QJsonObject StubJsonObj() {
    QFile file;
    file.setFileName("./client/Network/src/UserData.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray byteArray = file.readAll();
    file.close();
    qDebug() << QJsonDocument::fromJson(byteArray).toJson(QJsonDocument::Compact).toStdString();
    return QJsonDocument::fromJson(byteArray).object();
}

UserData Deserializer::DeserializeUserData(std::vector<char> byteArray) {
    UserData data;
    auto jsonObj = ByteArrayToJsonObj(byteArray);
    // auto jsonObj = StubJsonObj();
    auto info = DeserializeUserInfo(jsonObj["UserInfo"].toObject());
    auto rooms = DeserializeVectorOfRooms(jsonObj["VectorOfRooms"].toArray());
    data.info = info;
    data.rooms = rooms;
    // DebugPrintUserData(data);
    return data;    
}

// RoomData Deserializer::DeserializeRoom(std::vector<char> byteArray) {}
