#include "TCPMessageRouter.hpp"

bool operator==(const QString& l, const UserConnection& r)
{
    return l == r.login;
}

bool operator!=(const QString& l, const UserConnection& r)
{
    return !(l == r.login);
}

TcpMessageRouter& TcpMessageRouter::operator=(TcpMessageRouter&& other)
{
    this->connectionMap = std::move(other.connectionMap);

    return *this;
}

void TcpMessageRouter::insert(const int roomId, UserConnection&& userConnection)
{
    auto roomCell = connectionMap.find(roomId);

    if (roomCell == connectionMap.end())
    {
        connectionMap.insert(const_cast<int&>(roomId), {std::move(userConnection)});

        return;
    }

    (*roomCell).push_back(std::move(userConnection));
}

void TcpMessageRouter::sendSignalToUsersFromRoom(const int roomId, const QString& login)
{
    auto roomCell = connectionMap.find(roomId);

    if (roomCell == connectionMap.end())
        return;

    for (const auto& elem : *roomCell)
        if (elem.login != login)
            elem.socket->write(std::to_string(roomId).c_str());
}

void TcpMessageRouter::slotNewConnection()
{
    auto clientSocket = server->nextPendingConnection();

    if (!primeSocket)
    {
        configurePrimeSocket(clientSocket);

        return;
    }

    qDebug() << "socket was connected";

    connect(clientSocket, &QTcpSocket::readyRead, this, &TcpMessageRouter::slotServerRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, [clientSocket, this]()
    {
        for (auto it = connectionMap.begin(); it != connectionMap.end(); ++it)
            for (auto vIt = it->begin(); vIt != it->end(); ++vIt)
            {
                if (vIt->socket == clientSocket)
                {
                    vIt->socket->close();

                    it->erase(vIt);

                    qDebug() << "socket was closed\n";

                    return;
                }
            }
    });

    socketQueue.enqueue(clientSocket);
}

void TcpMessageRouter::slotServerRead()
{
    auto socket = socketQueue.dequeue();

    while (socket->bytesAvailable() > 0)
    {
        auto data = socket->readAll();

        qDebug() << data;

        auto splitted = data.split(
            *const_cast<char*>(" ") // Я ради этого изучаю С++
        );

        auto user = UserConnection(splitted[1], socket);

        insert(splitted[0].toInt(), std::move(user));

    }
}

void TcpMessageRouter::slotPrimeSocketRead()
{
    while (primeSocket->bytesAvailable() > 0)
    {
        auto data = primeSocket->readAll();

        qDebug() << data;

        auto splitted = data.split(' ');

        sendSignalToUsersFromRoom(splitted[0].toInt(), splitted[1]);

    }
}

void TcpMessageRouter::configurePrimeSocket(QTcpSocket* socket)
{
    primeSocket = socket;

    qDebug() << "prime socket was connected";

    connect(primeSocket, &QTcpSocket::readyRead, this, &TcpMessageRouter::slotPrimeSocketRead);
    connect(primeSocket, &QTcpSocket::disconnected, this, [this]()
    {
        this->primeSocket->close();

        qDebug() << "prime socket was closed\n";
    });
}