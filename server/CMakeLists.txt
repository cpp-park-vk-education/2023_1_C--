cmake_minimum_required(VERSION 3.14)

project(server LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Network Sql)

find_package(SFML REQUIRED system network)

include_directories(
    HttpRequest
    HttpResponse
    HttpHandlers
    Services
    Adapters
    Services/CreateRoomService
    Services/GetRoomHistoryService
    Services/LoginService
    Services/JoinRoomService
    Services/DeleteRoomService
    Services/GetNewMessageService
    Services/SendMessageService
    Services/RegisterService
    Services/SearchRoomService
    Services/RefreshRoomService
    HttpControllers
    HttpControllers/CreateRoomController
    HttpControllers/LoginController
    HttpControllers/JoinRoomController
    HttpControllers/DeleteRoomController
    HttpControllers/GetNewMessageController
    HttpControllers/SendMessageController
    HttpControllers/GetRoomHistoryController
    HttpControllers/RegisterController
    HttpControllers/SearchRoomController
    HttpControllers/RefreshRoomController
)

add_executable(server
    main.cpp
    Adapters/RequestMapperAdapter.cpp
    Adapters/HttpRequestToIHttpRequestAdapter.cpp
    Adapters/HttpResponseToIHttpResponseAdapter.cpp
    HttpHandlers/HttpRequestMapper.cpp
    Services/CreateRoomService/CreateRoomService.cpp
    Services/LoginService/LoginService.cpp
    Services/JoinRoomService/JoinRoomService.cpp
    Services/DeleteRoomService/DeleteRoomService.cpp
    Services/GetNewMessageService/GetNewMessageService.cpp
    Services/SendMessageService/SendMessageService.cpp
    Services/GetRoomHistoryService/GetRoomHistoryService.cpp
    Services/RegisterService/RegisterService.cpp
    Services/SearchRoomService/SearchRoomService.cpp
    Services/RefreshRoomService/RefreshRoomService.cpp
    HttpControllers/CreateRoomController/CreateController.cpp
    HttpControllers/LoginController/LoginController.cpp
    HttpControllers/JoinRoomController/JoinRoomController.cpp
    HttpControllers/DeleteRoomController/DeleteRoomController.cpp
    HttpControllers/GetNewMessageController/GetNewMessageController.cpp
    HttpControllers/SendMessageController/SendMessageController.cpp
    HttpControllers/GetRoomHistoryController/GetRoomHistoryController.cpp
    HttpControllers/RegisterController/RegisterController.cpp
    HttpControllers/SearchRoomController/SearchRoomController.cpp
    HttpControllers/RefreshRoomController/RefreshRoomController.cpp
)

target_include_directories(server PUBLIC ../DB/include)

target_link_libraries(server DB /usr/local/lib/libQtWebApp.so.1.8.6 Qt5::Core Qt5::Network Qt5::Sql sfml-system sfml-network)

install(TARGETS server
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})