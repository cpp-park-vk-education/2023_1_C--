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
#include "RefreshRoomController.hpp"
#include "DBManager.hpp"
#include "ClientDBManager.hpp"
#include "RoomDBManager.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    app.setApplicationName("Teamgram Server");

    auto settings = new QSettings("./server/config.ini", QSettings::IniFormat, &app); // "./server/config.ini" ../../server/config.ini

    settings->beginGroup("listener");

    auto manager = std::make_shared<DBManager>();

    auto clientDb = std::make_shared<ClientDBManager>(manager);

    auto roomDb = std::make_shared<RoomDBManager>(manager);

    auto mapper = std::make_unique<HttpRequestMapper>();

    mapper->addController<LoginController, LoginService>("/path", clientDb, roomDb);

    mapper->addController<JoinRoomController, JoinRoomService>("/join", clientDb, roomDb);

    mapper->addController<SendMessageController, SendMessageService>("/send", roomDb);

    mapper->addController<GetNewMessageController, GetNewMessageService>("/getmsg", roomDb);

    mapper->addController<CreateRoomController, CreateRoomService>("/create", clientDb, roomDb);

    mapper->addController<GetRoomHistoryController, GetRoomHistoryService>("/history", roomDb);

    mapper->addController<SearchRoomController, SearchRoomService>("/search", clientDb, roomDb);

    mapper->addController<RefreshRoomController, RefreshRoomService>("/refresh", clientDb, roomDb);

    mapper->addController<RegisterController, RegisterService>("/refresh", clientDb);
    
    try
    {
        new HttpListener(
            settings, 
            new RequestMapperAdapter(
                std::move(mapper), &app
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