#pragma once
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "Serializer.hpp"

std::vector<char> Serializer::SerializeLoginData(const LoginData& data) {
    QJsonObject jsonObject;
    jsonObject.insert("login", QJsonValue(QString::fromStdString(data.login)));
    jsonObject.insert("password", QJsonValue(QString::fromStdString(data.password)));
    //qDebug() << "Request data:";
    //qDebug() << QJsonDocument(jsonObject).toJson(QJsonDocument::Compact).toStdString();
    auto byteArray = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);
    return std::vector<char>(byteArray.begin(), byteArray.end());
}
std::vector<char> Serializer::SerializeSignupData(const SignupData& data) {}
std::vector<char> Serializer::SerializeUserSettingData(const UserSettingData& data) {}
std::vector<char> Serializer::SerializeLogoutData(const LogoutData& data) {}
std::vector<char> Serializer::SerializeString(const std::string& data) {}
std::vector<char> Serializer::SerializeMessage(const Message& data) {}
std::vector<char> Serializer::SerializeRoomInfo(const RoomInfo& data) {}
