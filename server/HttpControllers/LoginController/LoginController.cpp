#include "LoginController.hpp"

void LoginController::service(IHttpRequest* request, IHttpResponse* response) // WIP
{
    auto client = loginService->getClient("pussykiller");

    QJsonObject jsonObject;

    jsonObject.insert("login", client.login);

    jsonObject.insert("password", client.password);

    response->setBody(QJsonDocument(jsonObject).toJson(QJsonDocument::Compact).toStdString());
}