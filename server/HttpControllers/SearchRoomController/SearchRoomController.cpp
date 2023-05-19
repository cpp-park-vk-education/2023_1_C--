#include "SearchRoomController.hpp"

void SearchRoomController::service(IHttpRequest* request, IHttpResponse* response)
{
    auto jsonStr = request->getBody();

    auto requestJSONObject = QJsonDocument::fromJson(
        QByteArray::fromStdString(jsonStr)
    ).object();

    if(jsonStr.empty())
    {
        response->setStatus(401, "bad request body");

        return;
    }

    auto rooms = searchService->search(requestJSONObject.value("RoomName").toString().toStdString());

    QJsonObject responseJSONObject;

    fillRoomJsonResponse(responseJSONObject, QVector<Room>::fromStdVector(rooms));

    response->setBody(QJsonDocument(responseJSONObject).toJson(QJsonDocument::Compact).toStdString());
}

void SearchRoomController::fillRoomJsonResponse(QJsonObject& json, const QVector<Room>& rooms)
{
    QJsonArray roomArray;

    for (const auto& room : rooms)
    {
        QJsonObject jRoom;

        auto clientsInRoom = searchService->getClients(room.ID);
        
        QJsonArray members;
        
        for (const auto& member : clientsInRoom)
            members.append(member.username);

        jRoom.insert("RoomInfo", QJsonValue({
            qMakePair(QString::fromStdString("ID"), QJsonValue(room.ID)),
            qMakePair(QString::fromStdString("Name"), QJsonValue(room.name)),
            qMakePair(QString::fromStdString("Members"), QJsonValue(members))
            }));

        roomArray.append(jRoom);
    }

    json.insert("VectorOfRooms", roomArray);
}