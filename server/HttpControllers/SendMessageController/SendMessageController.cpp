#include "SendMessageController.hpp"

void SendMessageController::service(IHttpRequest* request, IHttpResponse* response)
{
    auto jsonStr = request->getBody();

    auto requestJSONObject = QJsonDocument::fromJson(
        QByteArray::fromStdString(jsonStr)
    ).object();

    auto content = requestJSONObject.value("Content").toString();

    if (!content.size())
    {
        response->setStatus(401, "empty content");

        return;
    }

    auto id = requestJSONObject.value("ID").toInt();

    auto login = requestJSONObject.value("Author").toString();

    sendService->SendMessage(
        id,
        login.toStdString(),
        content.toStdString()
    );

    messageRouter->sendSignalToUsersFromRoom(id, login);  
}