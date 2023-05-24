#include "LoginController.hpp"
#include <QVector>

void LoginController::service(IHttpRequest* request, IHttpResponse* response)
{

    auto jsonStr = request->getBody();

    auto requestJSONObject = QJsonDocument::fromJson(
        QByteArray::fromStdString(jsonStr)
    ).object();


    auto client = loginService->getClient(requestJSONObject.value("Login").toString().toStdString());

    if (!client.login.size())
    {
        response->setStatus(401, "bad login");

        return;
    }

    auto hashPassword = QCryptographicHash::hash(
        requestJSONObject.value("Password").toString().toUtf8(), QCryptographicHash::Algorithm::Sha256
    );

#pragma region pizdec
    if (!hashPassword.isEmpty())
        if (client.password != hashPassword)
        {
            response->setStatus(401, "password missmatch");

            return;
        }
#pragma endregion

    auto rooms = loginService->getClientRooms(client.login.toStdString());

    QJsonObject responseJSONObject;

    fillJsonClient(responseJSONObject, client);

    fillJsonRooms(responseJSONObject, QVector<Room>::fromStdVector(rooms));

    response->setBody(QJsonDocument(responseJSONObject).toJson(QJsonDocument::Compact).toStdString());
}

void LoginController::fillJsonClient(QJsonObject& json, const Client& client)
{
    json.insert("UserInfo", QJsonValue({
        qMakePair(QString::fromStdString("Login"), QJsonValue(client.login)),
        qMakePair(QString::fromStdString("Nickname"), QJsonValue(client.username)),
        qMakePair(QString::fromStdString("FirstName"), QJsonValue(client.firstName)),
        qMakePair(QString::fromStdString("LastName"), QJsonValue(client.lastName)),
        })
    );
}

void LoginController::fillJsonRooms(QJsonObject& json, const QVector<Room>& rooms)
{
    QJsonArray roomArray;

    for (const auto& room : rooms)
    {
        auto clientsInRoom = loginService->getClients(room.ID);
        
        QJsonArray members;
        
        for (const auto& member : clientsInRoom)
            members.append(
                QJsonObject({
                    qMakePair(QString::fromStdString("Login"), QJsonValue(member.login)),
                    qMakePair(QString::fromStdString("Nickname"), QJsonValue(member.username)),
                    qMakePair(QString::fromStdString("Firstname"), QJsonValue(member.firstName)),
                    qMakePair(QString::fromStdString("Lastname"), QJsonValue(member.lastName))
                })
            );

        QJsonObject roomInfo;

        roomInfo.insert("RoomInfo", QJsonValue({
            qMakePair(QString::fromStdString("Members"), QJsonValue(members)),
            qMakePair(QString::fromStdString("ID"), QJsonValue(room.ID)),
            qMakePair(QString::fromStdString("Name"), QJsonValue(room.name))
            }));

        roomArray.append(roomInfo);
    }

    json.insert("VectorOfRooms", roomArray);
}