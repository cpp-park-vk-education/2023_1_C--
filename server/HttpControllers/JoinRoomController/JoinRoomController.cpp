#include "JoinRoomController.hpp"

void JoinRoomController::service(IHttpRequest* request, IHttpResponse* response)
{
    auto jsonStr = request->getBody();

    auto requestJSONObject = QJsonDocument::fromJson(
        QByteArray::fromStdString(jsonStr)
    ).object();

    joinService->joinRoom(
        requestJSONObject.value("RoomId").toInt(),
        requestJSONObject.value("username").toString().toStdString()
    );
}