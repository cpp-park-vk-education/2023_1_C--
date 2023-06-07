#include "Room.hpp"

Room::Room(const QSqlQuery& query)
{
    ID = query.value(0).toInt();
    name = query.value(1).toString();
}
