#include <QCoreApplication>
#include <QtWebApp/httpserver/httplistener.h>
#include <iostream>

#include "HttpRequestMapper.hpp"
#include "LoginController.hpp"
#include "CreateController.hpp"
#include "JoinRoomController.hpp"
#include "RequestMapperAdapter.hpp"
#include "SendMessageController.hpp"
#include "GetNewMessageController.hpp"
#include "GetRoomHistoryController.hpp"
#include "RegisterController.hpp"
#include "SearchRoomController.hpp"
#include "DBManager.hpp"
#include <ClientDBManager.hpp>
#include <RoomDBManager.hpp>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    app.setApplicationName("Teamgram Server");

    auto settings = new QSettings("./server/config.ini", QSettings::IniFormat, &app);

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
            std::make_unique<JoinRoomService>(clientDb, roomDb)
        ))
    );

    map.insert(
        std::make_pair("/send", std::make_unique<SendMessageController>(
            std::make_unique<SendMessageService>(roomDb)
        ))
    );

    map.insert(
        std::make_pair("/getmsg", std::make_unique<GetNewMessageController>(
            std::make_unique<GetNewMessageService>(roomDb)
        ))
    );

    map.insert(
        std::make_pair("/create", std::make_unique<CreateRoomController>(
            std::make_unique<CreateRoomService>(clientDb, roomDb)
        ))
    );

    map.insert(
        std::make_pair("/history", std::make_unique<GetRoomHistoryController>(
            std::make_unique<GetRoomHistoryService>(roomDb)
        ))
    );

    map.insert(
        std::make_pair("/register", std::make_unique<RegisterController>(
            std::make_unique<RegisterService>(clientDb)
        ))
    );

    map.insert(
        std::make_pair("/search", std::make_unique<SearchRoomController>(
            std::make_unique<SearchRoomService>(clientDb, roomDb)
        ))
    );
    
    try
    {
        new HttpListener(
            settings, 
            new RequestMapperAdapter(
                std::make_unique<HttpRequestMapper>(std::move(map)), &app
            ),
            &app);
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << "\n";

        return 1;
    }

    return app.exec();
}