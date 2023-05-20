#include "JoinRoomController.hpp"

void JoinRoomController::service(IHttpRequest* request, IHttpResponse* response)
{
    auto jsonStr = request->getBody();

    auto requestJSONObject = QJsonDocument::fromJson(
        QByteArray::fromStdString(jsonStr)
    ).object();

    auto client = joinService->findClient(
        requestJSONObject.value("Login").toString().toStdString()
    );

    if (client.login.isEmpty())
    {
        response->setStatus(401, "Bad User Login.");

        return;
    }

    joinService->joinRoom(
        requestJSONObject.value("RoomID").toInt(),
        requestJSONObject.value("Login").toString().toStdString()
    );

    QJsonObject responseJSONObject;

    responseJSONObject.insert("UserInfo", QJsonValue({
        qMakePair(QString::fromStdString("Login"), QJsonValue(client.login)),
        qMakePair(QString::fromStdString("Nickname"), QJsonValue(client.username)),
        qMakePair(QString::fromStdString("FirstName"), QJsonValue(client.firstName)),
        qMakePair(QString::fromStdString("LastName"), QJsonValue(client.lastName)),
        })
    );

    response->setBody(QJsonDocument(responseJSONObject).toJson(QJsonDocument::Compact).toStdString());
}