cmake_minimum_required(VERSION 3.14)

project(server LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Network Sql)
find_package(Qt5 REQUIRED COMPONENTS Core Network Sql)

include_directories(
    HttpRequest
    HttpResponse
    HttpHandlers
    Services
    Adapters
    Services/CreateRoomService
    Services/LoginService
    Services/JoinRoomService
    Services/DeleteRoomService
    Services/GetNewMessageService
    Services/SendMessageService
    HttpControllers
    HttpControllers/CreateRoomController
    HttpControllers/LoginController
    HttpControllers/JoinRoomController
    HttpControllers/DeleteRoomController
    HttpControllers/GetNewMessageController
    HttpControllers/SendMessageController
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
    HttpControllers/CreateRoomController/CreateController.cpp
    HttpControllers/LoginController/LoginController.cpp
    HttpControllers/JoinRoomController/JoinRoomController.cpp
    HttpControllers/DeleteRoomController/DeleteRoomController.cpp
    HttpControllers/GetNewMessageController/GetNewMessageController.cpp
    HttpControllers/SendMessageController/SendMessageController.cpp
)

target_include_directories(server PUBLIC ../DB/include)

target_link_libraries(server DB)

target_link_libraries(server -lQtWebApp)

target_link_libraries(server Qt5::Core Qt5::Network Qt5::Sql)

install(TARGETS server
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})