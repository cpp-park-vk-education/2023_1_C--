#include "Message.hpp"

Message::Message(const QSqlQuery& query)
{
    ID = query.value(0).toInt();
    roomID = query.value(1).toInt();
    user = query.value(2).toString();
    context = query.value(3).toString();
    date = query.value(4).toDateTime();
}
