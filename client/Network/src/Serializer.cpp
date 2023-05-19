#include <vector>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "Serializer.hpp"
#include "SerializationKeys.hpp"

static std::vector<char> GetByteArray(const QJsonObject& jsonObject) {
    auto byteArray = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);
    // qDebug() << QJsonDocument(jsonObject).toJson(QJsonDocument::Compact).toStdString();
    return std::vector<char>(byteArray.begin(), byteArray.end());
}

std::vector<char> Serializer::SerializeLoginData(const LoginData& data) {
    QJsonObject jsonObject;
    jsonObject.insert(LOGIN_KEY, QJsonValue(QString::fromStdString(data.login)));
    jsonObject.insert(PASSWORD_KEY, QJsonValue(QString::fromStdString(data.password)));
    auto byteArray = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);
    return std::vector<char>(byteArray.begin(), byteArray.end());
}

std::vector<char> Serializer::SerializeSignupData(const SignupData& data) {
    QJsonObject jsonObject;
    jsonObject.insert(LOGIN_KEY, QJsonValue(QString::fromStdString(data.login)));
    jsonObject.insert(PASSWORD_KEY, QJsonValue(QString::fromStdString(data.password)));
    jsonObject.insert(NICKNAME_KEY, QJsonValue(QString::fromStdString(data.nickname)));
    jsonObject.insert(FIRSTNAME_KEY, QJsonValue(QString::fromStdString(data.firstName)));
    jsonObject.insert(LASTNAME_KEY, QJsonValue(QString::fromStdString(data.lastName)));
    return GetByteArray(jsonObject);
}

std::vector<char> Serializer::SerializeID(const int id) {
    QJsonObject jsonObject;
    jsonObject.insert(ID_KEY, QJsonValue(id));
    auto data = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact).toStdString();
    return GetByteArray(jsonObject);
}

std::vector<char> Serializer::SerializeMessage(const Message& data) {
    QJsonObject jsonObject;
    jsonObject.insert(AUTHOR_KEY, QJsonValue(QString::fromStdString(data.author)));
    jsonObject.insert(CONTENT_KEY, QJsonValue(QString::fromStdString(data.content)));
    jsonObject.insert(ID_KEY, QJsonValue(data.roomID));
    return GetByteArray(jsonObject);
}

std::vector<char> Serializer::SerializeRoomInfo(const RoomInfo& data) {
    QJsonObject jsonObject;
    jsonObject.insert(NAME_KEY, QJsonValue(QString::fromStdString(data.name)));
    QJsonArray members;
    for (const auto member : data.members)
        members.append(QJsonValue(QString::fromStdString(member)));
    jsonObject.insert(MEMBERS_KEY, members);
    return GetByteArray(jsonObject); 
}

