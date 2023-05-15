#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "Serializer.hpp"
#include "SerializationKeys.hpp"

// static QJsonObject SerializeVectorOfMembers(const std::vector<std::string>& members)
// {
//     json.insert("UserInfo", QJsonValue({
//         qMakePair(QString::fromStdString("Login"), QJsonValue(client.login)),
//         qMakePair(QString::fromStdString("Nickname"), QJsonValue(client.username)),
//         qMakePair(QString::fromStdString("Password"), QJsonValue(client.password)),
//         qMakePair(QString::fromStdString("FirstName"), QJsonValue(client.firstName)),
//         qMakePair(QString::fromStdString("LastName"), QJsonValue(client.lastName)),
//         })
//     );
// }

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
    auto byteArray = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);
    qDebug() << QJsonDocument(jsonObject).toJson(QJsonDocument::Compact).toStdString();
    return std::vector<char>(byteArray.begin(), byteArray.end());
}

std::vector<char> Serializer::SerializeUserSettingData(const UserSettingData& data) {}
std::vector<char> Serializer::SerializeLogoutData(const LogoutData& data) {}
std::vector<char> Serializer::SerializeString(const std::string& data) {}
std::vector<char> Serializer::SerializeMessage(const Message& data) {}

std::vector<char> Serializer::SerializeRoomInfo(const RoomInfo& data) {
    QJsonObject jsonObject;
    jsonObject.insert(NAME_KEY, QJsonValue(QString::fromStdString(data.name)));
    
    QJsonArray members;
    for_each(data.members.begin(), data.members.end(), [&members](const std::string username){
        members.append(QJsonValue(QString::fromStdString(username)));
    });
    jsonObject.insert(MEMBERS_KEY, members);

    auto byteArray = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);
    qDebug() << QJsonDocument(jsonObject).toJson(QJsonDocument::Compact).toStdString();
    return std::vector<char>(byteArray.begin(), byteArray.end());
}
