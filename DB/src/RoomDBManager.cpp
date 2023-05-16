#include "RoomDBManager.hpp"

const std::string NO_SUCH_ROOM_ERROR = "There is no such room!";
const std::string SMTH_WENT_WRONG_ERROR = "Something went wrong!";

RoomDBManager::RoomDBManager(std::shared_ptr<DBManager>& manager) {
    dbManager = manager;
}

Room RoomDBManager::getRoom(const int room_ID) {
    const QString queryStr = "SELECT * FROM rooms WHERE ID = " + QString::number(room_ID);
    QSqlQuery query;
    try {
        query = dbManager->execute(queryStr);
    } catch (const std::runtime_error& err) {
        throw std::runtime_error(NO_SUCH_ROOM_ERROR);
    }
    Room room = Room(query);
    return room;
}

QVector<Room> RoomDBManager::getRooms(const QString& login) {
    const QString queryStr = "SELECT * FROM rooms WHERE id IN (SELECT room_id FROM users_rooms WHERE login='" 
        + login + "');";
    QSqlQuery query;
    try {
        query = dbManager->execute(queryStr);
    } catch (const std::runtime_error& err) {
        throw std::runtime_error(NO_SUCH_ROOM_ERROR);
    }
    QVector<Room> rooms;
    rooms.push_back(Room(query));
    while(query.next())
    {
         rooms.push_back(Room(query));
    }
    return rooms;
}

QVector<Message> RoomDBManager::getMessages(const int roomID) {
    const QString queryStr = "SELECT * FROM messages "
                             "WHERE room_id = " + QString::number(roomID);
    QSqlQuery query; 
    try {
        query = dbManager->execute(queryStr);
    } catch (const std::runtime_error& err) {
        throw std::runtime_error(SMTH_WENT_WRONG_ERROR);
    }
    QVector<Message> messages;
    messages.push_back(Message(query));
    while(query.next())
    {
         messages.push_back(Message(query));
    }
    return messages;
}

Room RoomDBManager::insertRoom(const QString& username, const QString& roomname) {
    const QString queryStr = "INSERT INTO rooms (room_name) VALUES ('" + roomname + "');";
    try {
        dbManager->execute(queryStr);
    } catch (const std::runtime_error& err) {
        throw std::runtime_error(SMTH_WENT_WRONG_ERROR);
    }

    const QString queryStr2 = "SELECT * FROM rooms ORDER BY id DESC LIMIT 1";
    try {
        dbManager->execute(queryStr);
    } catch (const std::runtime_error& err) {
        throw std::runtime_error(SMTH_WENT_WRONG_ERROR);
    }
    Room room = Room(query);
    addClientToRoom(room.ID, username);    
    return room;
}

Message RoomDBManager::insertNewMessage(const int room_ID, const QString& username, const QString& text) {
    QDateTime curr_DT = QDateTime::currentDateTime();
    QString date = QString::number(curr_DT.date().year()) + "-" + QString::number(curr_DT.date().month()) +
                   "-" + QString::number(curr_DT.date().day()) + " " + QString::number(curr_DT.time().hour()) + ":" +
                   QString::number(curr_DT.time().minute()) + ":" + QString::number(curr_DT.time().second());
    QString queryStr = "INSERT INTO messages (room_id, username, context, date) VALUES (" + QString::number(room_ID) + ", '" + username +
        "', '" + text + "', '" + date + "');";
    try {
        dbManager->execute(queryStr);
    } catch (const std::runtime_error& err) {
        throw std::runtime_error(SMTH_WENT_WRONG_ERROR);
    }
    Message message = getNewMessage(room_ID);
    return message;
}

Message RoomDBManager::getNewMessage(const int room_ID) {
    const QString queryStr = "SELECT * FROM messages "
            "WHERE room_id = " + QString::number(room_ID) + " ORDER BY date DESC LIMIT 1;";
    QSqlQuery query; 
    try {
        query = dbManager->execute(queryStr);
    } catch (const std::runtime_error& err) {
        throw std::runtime_error(SMTH_WENT_WRONG_ERROR);
    }
    Message message = Message(query);
    return message;
}

void RoomDBManager::deleteRoom(const int room_ID) {
    const QString queryStr = "DELETE FROM rooms WHERE room_id = " + QString::number(room_ID);
    try {
        dbManager->execute(queryStr);
    } catch (const std::runtime_error& err) {
        throw std::runtime_error(NO_SUCH_ROOM_ERROR);
    }
}

Room RoomDBManager::renameRoom(const int roomID, const QString& new_name) {
    const QString queryStr = "UPDATE rooms "
            "SET name = '" + new_name + ""
            "'WHERE room_id = " + QString::number(roomID);
    try {
        dbManager->execute(queryStr);
    } catch (const std::runtime_error& err) {
        throw std::runtime_error(NO_SUCH_ROOM_ERROR);
    }
    return getRoom(roomID); 
}

void RoomDBManager::addClientToRoom(const int room_ID, const QString& username) {
    const QString queryStr = "INSERT INTO users_rooms VALUES (" + QString::number(room_ID) + ", '" + username + "');";
    try {
        dbManager->execute(queryStr);
    } catch (const std::runtime_error& err) {
        throw std::runtime_error(SMTH_WENT_WRONG_ERROR);
    }
}

void RoomDBManager::deleteClientFromRoom(const int room_ID, const QString& username) {
    const QString queryStr = "DELETE FROM rooms WHERE room_id = " + QString::number(room_ID) + ""
                             "AND username = '" + username + "';";
    try {
        dbManager->execute(queryStr);
    } catch (const std::runtime_error& err) {
        throw std::runtime_error(SMTH_WENT_WRONG_ERROR);
    }
}

Message RoomDBManager::changeMessageContext(const int message_ID, const QString& new_context) {
    const QString queryStr = "UPDATE messages "
            "SET context = '" + new_context + ""
                                             "'WHERE ID = " + QString::number(message_ID);
    try {
        dbManager->execute(queryStr);
    } catch (const std::runtime_error& err) {
        throw std::runtime_error(SMTH_WENT_WRONG_ERROR);
    }
    return getMessage(message_ID);
}

Message RoomDBManager::getMessage(const int message_ID) {
    const QString queryStr = "SELECT * FROM messages WHERE ID = " + QString::number(message_ID);
    QSqlQuery query; 
    try {
        query = dbManager->execute(queryStr);
    } catch (const std::runtime_error& err) {
        throw std::runtime_error(SMTH_WENT_WRONG_ERROR);
    }
    Message message = Message(query);
    return message;
}

QVector<Room> RoomDBManager::searchRooms(const QString& roomName) {
    const QString queryStr = "SELECT * FROM rooms "
            "WHERE roomname = '" + roomName + "'";
    QSqlQuery query; 
    try {
        query = dbManager->execute(queryStr);
    } catch (const std::runtime_error& err) {
        throw std::runtime_error(NO_SUCH_ROOM_ERROR);
    }
    QVector<Room> rooms;
    while(query.next())
    {
        rooms.push_back(Room(query));
    }
    return rooms;
}