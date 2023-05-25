#pragma once

#include <QObject>
#include <QVector>
#include <QTcpSocket>
#include <QMap>
#include <QString>
#include <memory>
#include <QTcpServer>
#include <QQueue>

class UserConnection
{
public:
    UserConnection() {}
    UserConnection(const QString& login, QTcpSocket* socket)
        : login(login), socket(socket){}
    friend bool operator==(const QString& l, const UserConnection& r);

    friend bool operator!=(const QString& l, const UserConnection& r);

    friend class TcpMessageReciver;

private:
    QString login;

    QTcpSocket* socket;
};

class TcpMessageReciver : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(TcpMessageReciver)
public:

    explicit TcpMessageReciver(QObject* parent = (QObject*)nullptr) : QObject(parent)
    {
        server = new QTcpServer(this);

        connect(server, &QTcpServer::newConnection, this, &TcpMessageReciver::slotNewConnection);

        if (!server->listen(QHostAddress("127.0.0.1"), 8080))
            qDebug() << "Router error\n";
        else qDebug() << "Router started on port 8080\n";
    }

    TcpMessageReciver& operator=(TcpMessageReciver&& other);

    void sendSignalToUsersFromRoom(const int roomId, const QString& login);

public slots:
    void slotNewConnection();

    void slotServerRead();

private:
    void insert(const int roomId, UserConnection&& userConnection);

    QTcpServer* server;

    QQueue<QTcpSocket*> socketQueue;

    QMap<int, QVector<UserConnection>> connectionMap;
};

