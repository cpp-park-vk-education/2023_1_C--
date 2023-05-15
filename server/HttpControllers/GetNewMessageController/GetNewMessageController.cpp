#include "GetNewMessageController.hpp"

void GetNewMessageController::service(IHttpRequest* request, IHttpResponse* response)
{
    auto jsonStr = request->getBody();

    auto requestJSONObject = QJsonDocument::fromJson(
        QByteArray::fromStdString(jsonStr)
    ).object();

    auto msg = getMessageService->getNewMessage(
        requestJSONObject.value("ID").toString().toInt()
    );

    QJsonObject responseJSONObject;

    fillJSONMessage(responseJSONObject, msg);

    response->setBody(QJsonDocument(responseJSONObject).toJson(QJsonDocument::Compact).toStdString());
}

void GetNewMessageController::fillJSONMessage(QJsonObject& json, const Message& message)
{
    json.insert("Message", QJsonValue({
        qMakePair(QString::fromStdString("ID"), QJsonValue(message.ID)),
        qMakePair(QString::fromStdString("Content"), QJsonValue(message.context)),
        qMakePair(QString::fromStdString("Author"), QJsonValue(message.user)),
        qMakePair(QString::fromStdString("SendingData"), QJsonValue(message.date.toString()))
        })
    );
}