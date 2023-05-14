#include <QCoreApplication>
#include <QtWebApp/httpserver/httplistener.h>

#include "HttpRequestMapper.hpp"
#include "LoginController.hpp"
#include "JoinRoomController.hpp"
#include "RequestMapperAdapter.hpp"
#include "SendMessageController.hpp"
#include "DBManager.hpp"
#include <ClientDBManager.hpp>
#include <RoomDBManager.hpp>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    app.setApplicationName("Teamgram Server");

    auto settings = new QSettings("../../server/config.ini", QSettings::IniFormat, &app);

    settings->beginGroup("listener");

    auto manager = std::make_shared<DBManager>();

    auto clientDb = std::make_shared<ClientDBManager>(manager);

    auto roomDb = std::make_shared<RoomDBManager>(manager);

    std::map<std::string, std::unique_ptr<IHttpRequestHandler>> map;

    map.insert(
        std::make_pair("/login", std::make_unique<LoginController>(
            std::make_unique<LoginService>(clientDb, roomDb)
        ))
    );

    map.insert(
        std::make_pair("/join", std::make_unique<JoinRoomController>(
            std::make_unique<JoinRoomService>(roomDb)
        ))
    );

    map.insert(
        std::make_pair("/send", std::make_unique<SendMessageController>(
            std::make_unique<SendMessageService>(roomDb)
        ))
    );
    
    new HttpListener(
        settings, 
        new RequestMapperAdapter(
            std::make_unique<HttpRequestMapper>(std::move(map)), &app
        ),
        &app);

    app.exec();
}