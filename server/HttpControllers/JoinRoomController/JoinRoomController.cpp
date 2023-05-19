#include "JoinRoomController.hpp"

void JoinRoomController::service(IHttpRequest* request, IHttpResponse* response)
{
    auto jsonStr = request->getBody();

    auto requestJSONObject = QJsonDocument::fromJson(
        QByteArray::fromStdString(jsonStr)
    ).object();

    joinService->joinRoom(
        requestJSONObject.value("RoomID").toInt(),
        requestJSONObject.value("Login").toString().toStdString()
    );
}