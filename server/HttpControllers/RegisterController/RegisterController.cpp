#include "RegisterController.hpp"

void RegisterController::service(IHttpRequest* request, IHttpResponse* response)
{

    auto jsonStr = request->getBody();

    auto requestJSONObject = QJsonDocument::fromJson(
        QByteArray::fromStdString(jsonStr)
    ).object();

    auto login = requestJSONObject.value("Login").toString();
    auto password = requestJSONObject.value("Password").toString();
    auto username = requestJSONObject.value("Nickname").toString();

    if (!checkArgs(login, password, username))
    {
        response->setStatus(401, "bad register fields");

        return;
    }

    registerService->regClient(
        login.toStdString(),
        password.toStdString(),
        username.toStdString()
    );

    QJsonObject responseJSONObject;

    responseJSONObject.insert("UserInfo", QJsonValue({
    qMakePair(QString::fromStdString("Login"), QJsonValue(login)),
    qMakePair(QString::fromStdString("Nickname"), QJsonValue(username))
        })
    );

    response->setBody(QJsonDocument(responseJSONObject).toJson(QJsonDocument::Compact).toStdString());
    
}