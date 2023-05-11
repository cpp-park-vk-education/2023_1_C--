#include "Client.hpp"

Client::Client(const QSqlQuery& query)
{
    login = query.value(0).toString();
    password = query.value(1).toString();
    username = query.value(2).toString();
    firstName = query.value(3).toString();
    lastName = query.value(4).toString();
}
