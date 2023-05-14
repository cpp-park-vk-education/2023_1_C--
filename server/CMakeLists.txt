cmake_minimum_required(VERSION 3.14)

project(server LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Network)
find_package(Qt${QT_VEwRSION_MAJOR} REQUIRED COMPONENTS Core Network)

include_directories(
    HttpRequest
    HttpResponse
    HttpHandlers
    DbInterface
    Services
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

set(WEB_DIR ../QtWebApp)

target_link_libraries(server /usr/local/lib/libQtWebApp.so.1.8.6)
target_include_directories(server PUBLIC ${WEB_DIR}/httpserver ${WEB_DIR}/logging ${WEB_DIR}/templateengine)
target_link_libraries(server Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)

install(TARGETS server
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})