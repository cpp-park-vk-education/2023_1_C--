#include "RoomDBManager.hpp"

RoomDBManager::RoomDBManager(std::shared_ptr<DBManager>& manager) {
    dbManager = manager;
}

Room RoomDBManager::getRoom(const int room_ID) {
    const QString queryStr = "SELECT * FROM rooms WHERE ID = " + room_ID;
    QSqlQuery query = dbManager->execute(queryStr);
    Room room = Room(query);
    return room;
}

QList<Room> RoomDBManager::getRooms(const QString& username) {
    const QString queryStr = "SELECT * FROM rooms "
            "WHERE username = '" + username + "'";
    QSqlQuery query = dbManager->execute(queryStr);
    QList<Room> rooms;
    rooms.push_back(Room(query));
    while(query.next())
    {
         rooms.push_back(Room(query));
    }
    return rooms;
}

QList<Message> RoomDBManager::getMessages(const int roomID, const QString& username) {
    const QString queryStr = "SELECT * FROM messages "
                             "WHERE room_id = " + QString::number(roomID) + ""
                             "AND username = '" + username + "'";
    QSqlQuery query = dbManager->execute(queryStr);
    QList<Message> messages;
    messages.push_back(Message(query));
    while(query.next())
    {
         messages.push_back(Message(query));
    }
    return messages;
}

Room RoomDBManager::insertRoom(const QString& username, const QString& roomname) {
    const QString queryStr = "INSERT INTO rooms VALUES ('" + roomname + "');";
    dbManager->execute(queryStr);
    Room room = getRooms(username).last();
    addClientToRoom(room.ID, username);
    return room;
}

Message RoomDBManager::insertNewMessage(const int room_ID, const QString& username, const QString& text) {
    QDateTime curr_DT = QDateTime::currentDateTime();
    QString date = QString::number(curr_DT.date().year()) + "-" + QString::number(curr_DT.date().month()) +
                   "-" + QString::number(curr_DT.date().day()) + " " + QString::number(curr_DT.time().hour()) + ":" +
                   QString::number(curr_DT.time().minute()) + ":" + QString::number(curr_DT.time().second());
    QString queryStr = "INSERT INTO rooms VALUES (" + QString::number(room_ID) + ", '" + username +
        ", '" + text + "'" + date + "');";
    dbManager->execute(queryStr);
    Message message = getNewMessage(room_ID);
}

Message RoomDBManager::getNewMessage(const int room_ID) {
    const QString queryStr = "SELECT * FROM messages "
            "WHERE room_id = " + room_ID;
    QSqlQuery query = dbManager->execute(queryStr);
    Message message;
    while(query.next())
    {
        message = Message(query);
    }
    return message;
}

void RoomDBManager::deleteRoom(const int room_ID) {
    const QString queryStr = "DELETE FROM rooms WHERE room_id = " + room_ID;
    dbManager->execute(queryStr);
}

Room RoomDBManager::renameRoom(const int roomID, const QString& new_name) {
    const QString queryStr = "UPDATE rooms "
            "SET name = '" + new_name + ""
            "'WHERE room_id = " + QString::number(roomID);
    dbManager->execute(queryStr);
    return getRoom(roomID); 
}

void RoomDBManager::addClientToRoom(const int room_ID, const QString& username) {
    const QString queryStr = "INSERT INTO user_rooms VALUES (" + QString::number(room_ID) + ", '" + username + "');";
    dbManager->execute(queryStr);
}

void RoomDBManager::deleteClientFromRoom(const int room_ID, const QString& username) {
    const QString queryStr = "DELETE FROM rooms WHERE room_id = " + QString::number(room_ID) + ""
                             "AND username = '" + username + "';";
    dbManager->execute(queryStr);
}

Message RoomDBManager::changeMessageContext(const int message_ID, const QString& new_context) {
    const QString queryStr = "UPDATE messages "
            "SET context = '" + new_context + ""
                                             "'WHERE ID = " + QString::number(message_ID);
    dbManager->execute(queryStr);
    return getMessage(message_ID);
}

Message RoomDBManager::getMessage(const int message_ID) {
    const QString queryStr = "SELECT * FROM messages WHERE ID = " + QString::number(message_ID);
    QSqlQuery query = dbManager->execute(queryStr);
    Message message = Message(query);
    return message;
}
