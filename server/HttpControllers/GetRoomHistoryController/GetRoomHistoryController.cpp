#include  "GetRoomHistoryController.hpp"

void GetRoomHistoryController::service(IHttpRequest* request, IHttpResponse* response)
{
    auto jsonStr = request->getBody();

    auto requestJSONObject = QJsonDocument::fromJson(
        QByteArray::fromStdString(jsonStr)
    ).object();

    auto messages = historyService->getMessages(
        requestJSONObject.value("ID").toString().toInt()
    );

    QJsonObject responseJSONObject;

    fillJSONMessage(responseJSONObject, QVector<Message>(messages.begin(), messages.end()));

    response->setBody(QJsonDocument(responseJSONObject).toJson(QJsonDocument::Compact).toStdString());
}

void GetRoomHistoryController::fillJSONMessage(QJsonObject& json, const QVector<Message>& messages)
{
    QJsonArray array;

    for (const auto& message : messages)
    {
        QJsonObject JsonMessage;

        JsonMessage.insert("Message", QJsonValue({
            qMakePair(QString::fromStdString("ID"), QJsonValue(message.ID)),
            qMakePair(QString::fromStdString("Content"), QJsonValue(message.context)),
            qMakePair(QString::fromStdString("Author"), QJsonValue(message.user)),
            qMakePair(QString::fromStdString("SendingData"), QJsonValue(message.date.toString()))
            })
        );

        array.append(JsonMessage);
    }

    json.insert("Messages", array);
}