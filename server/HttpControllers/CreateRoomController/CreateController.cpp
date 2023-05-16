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

    createService->CreateRoomWithUsers(stdLogins, roomName.toStdString());
}