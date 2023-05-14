#include "LoginController.hpp"

void LoginController::service(IHttpRequest* request, IHttpResponse* response) // WIP
{

    auto jsonStr = request->getBody();

    auto requestJSONObject = QJsonDocument::fromJson(
        QByteArray::fromStdString(jsonStr)
    ).object();


    auto client = loginService->getClient(requestJSONObject.value("login").toString().toStdString());

    if (!client.login.size())
    {
        response->setStatus(401, "bad login");

        return;
    }

    if (client.password != requestJSONObject.value("password").toString())
    {
        response->setStatus(401, "password missmatch");

        return;
    }

    auto rooms = loginService->getClientRooms(client.login.toStdString());

    QJsonObject responseJSONObject;

    fillJsonClient(responseJSONObject, client);

    fillJsonRooms(responseJSONObject, QVector<Room>(rooms.begin(), rooms.end()));

    response->setBody(QJsonDocument(responseJSONObject).toJson(QJsonDocument::Compact).toStdString());
}

void LoginController::fillJsonClient(QJsonObject& json, const Client& client)
{
    json.insert("UserInfo", QJsonValue({
        qMakePair(QString::fromStdString("login"), QJsonValue(client.login)),
        qMakePair(QString::fromStdString("nickname"), QJsonValue(client.username)),
        qMakePair(QString::fromStdString("password"), QJsonValue(client.password)),
        qMakePair(QString::fromStdString("firstName"), QJsonValue(client.firstName)),
        qMakePair(QString::fromStdString("lastName"), QJsonValue(client.lastName)),
        })
    );
}

void LoginController::fillJsonRooms(QJsonObject& json, const QVector<Room>& rooms)
{
    QJsonArray roomArray;

    for (const auto& room : rooms)
    {
        auto clientsInRoom = loginService->getClients(room.ID);

        qDebug() << clientsInRoom.size();
        
        QJsonArray members;
        
        for (const auto& member : clientsInRoom)
            members.append(member.username);

        QJsonObject roomInfo;

        roomInfo.insert("RoomInfo", QJsonValue({
            qMakePair(QString::fromStdString("members"), QJsonValue(members)),
            qMakePair(QString::fromStdString("name"), QJsonValue(room.name))
            }));

        roomArray.append(roomInfo);
    }

    json.insert("VectorOfRooms", roomArray);
}