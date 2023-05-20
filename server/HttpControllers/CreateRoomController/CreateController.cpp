#include "CreateController.hpp"

void CreateRoomController::service(IHttpRequest* request, IHttpResponse* response)
{
    auto jsonStr = request->getBody();

    auto requestJSONObject = QJsonDocument::fromJson(
        QByteArray::fromStdString(jsonStr)
    ).object();

    auto roomName = requestJSONObject.value("RoomName").toString();

    if (!roomName.size())
    {
        response->setStatus(401, "bad room name");

        return;
    }

    auto logins = requestJSONObject.value("Members").toArray();

    for (const auto& login : logins)
        if (!createService->isClientExists(login.toString().toStdString()))
        {
            response->setStatus(401, "user " + login.toString().toStdString() + " does not exist");

            return;
        }

    std::vector<std::string> stdLogins;
    for (const auto& login : logins)
        stdLogins.push_back(login.toString().toStdString());

    auto room = createService->CreateRoomWithUsers(stdLogins, roomName.toStdString());

    auto clients = createService->getClientsByLogin(stdLogins);

    QJsonObject responseJSONObject;

    fillJsonClients(responseJSONObject, clients);

    QJsonObject roomInfo;

    roomInfo.insert("RoomInfo", QJsonValue({
        qMakePair(QString::fromStdString("ID"), QJsonValue(room.ID)),
        qMakePair(QString::fromStdString("Name"), QJsonValue(room.name))
        }));

    responseJSONObject.insert("Room", roomInfo);

    response->setBody(QJsonDocument(responseJSONObject).toJson(QJsonDocument::Compact).toStdString());

}

void CreateRoomController::fillJsonClients(QJsonObject& json, const std::vector<Client>& clients)
{
    QJsonArray members;

    for (const auto& member : clients)
        members.append(
            QJsonObject({
                qMakePair(QString::fromStdString("Login"), QJsonValue(member.login)),
                qMakePair(QString::fromStdString("Username"), QJsonValue(member.username)),
                qMakePair(QString::fromStdString("Firstname"), QJsonValue(member.firstName)),
                qMakePair(QString::fromStdString("Lastname"), QJsonValue(member.lastName))
            })
        );

    json.insert("Members", members);
}
