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
        33,
        requestJSONObject.value("Login").toString().toStdString(),
        content.toStdString()
    );
}