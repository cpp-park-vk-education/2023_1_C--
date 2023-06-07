#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "Serializer.hpp"
#include "SerializationKeys.hpp"

static std::vector<char> GetByteArray(const QJsonObject& jsonObject) {
    auto byteArray = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);
    return std::vector<char>(byteArray.begin(), byteArray.end());
}

std::vector<char> Serializer::SerializeLoginData(const LoginData& data) {
    QJsonObject jsonObject;
    jsonObject.insert(LOGIN_KEY, QJsonValue(QString::fromStdString(data.login)));
    jsonObject.insert(PASSWORD_KEY, QJsonValue(QString::fromStdString(data.password)));
    auto byteArray = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);
    return GetByteArray(jsonObject);
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

std::vector<char> Serializer::SerializeMessage(const Message& data) {
    QJsonObject jsonObject;
    jsonObject.insert(AUTHOR_KEY, QJsonValue(QString::fromStdString(data.author)));
    jsonObject.insert(CONTENT_KEY, QJsonValue(QString::fromStdString(data.content)));
    jsonObject.insert(ID_KEY, QJsonValue(data.roomID));
    return GetByteArray(jsonObject);
}

std::vector<char> Serializer::SerializeRoomCreation(const std::string& name,
                                                    const std::vector<std::string>& members) {
    QJsonObject jsonObject;
    jsonObject.insert(ROOM_NAME_KEY, QJsonValue(QString::fromStdString(name)));
    QJsonArray membersJsonArray;
    for (const auto& memberLogin : members)
        membersJsonArray.append(QJsonValue(QString::fromStdString(memberLogin)));
    jsonObject.insert(MEMBERS_KEY, membersJsonArray);
    return GetByteArray(jsonObject); 
}

std::vector<char> Serializer::SerializeJoiningUser(const int roomID, 
                                                   const std::string& login) {
    QJsonObject jsonObject;
    jsonObject.insert(ROOM_ID_KEY, QJsonValue(roomID));
    jsonObject.insert(LOGIN_KEY, QJsonValue(QString::fromStdString(login)));
    return GetByteArray(jsonObject);
}

