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

    sendService->SendMessage(
        requestJSONObject.value("ID").toInt(),
        requestJSONObject.value("Author").toString().toStdString(),
        content.toStdString()
    );
}