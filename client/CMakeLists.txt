cmake_minimum_required(VERSION 3.14)

project(client LANGUAGES CXX)

option(BUILD_TESTS "build tests")

if(BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)

    add_compile_options(--coverage)
    add_link_options(--coverage)

    add_subdirectory(Account/tests)
    # add_subdirectory(Room/tests)
endif()
  
find_package(Qt5 REQUIRED COMPONENTS Widgets Network Core)

include_directories(Account/include
                    AppController
                    DataStructures
                    GUI
                    GUI/LoginPage
                    GUI/MainPage
                    GUI/MainWindow
                    GUI/MCLineEdit
                    GUI/RoomPage
                    GUI/RoomCreationPage
                    GUI/RoomSearchPage
                    GUI/SignupPage
                    Network/NetworkManager
                    Network/Request
                    Network/RequestCreator
                    Network/Response
                    Network/Serialization/include
                    Network/TcpConnection
                    Room/include)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(ACCOUNT_SOURCES Account/src/AccountNetwork.cpp
                    Account/src/AccountUseCase.cpp
                    Account/src/Forms.cpp)

set(ROOM_SOURCES    Room/src/RoomNetwork.cpp
                    Room/src/RoomUseCase.cpp)

set(NETWORK_SOURCES Network/NetworkManager/NetworkManager.cpp
                    Network/Serialization/src/Serializer.cpp
                    Network/Serialization/src/Deserializer.cpp
                    Network/TcpConnection/TcpConnection.cpp)  

SET(UI_SOURCES      GUI/MainWindow/MainWindow.hpp
                    GUI/MainWindow/MainWindow.cpp
                    GUI/MainWindow/MainWindow.ui
                    GUI/LoginPage/LoginPage.hpp
                    GUI/LoginPage/LoginPage.cpp
                    GUI/LoginPage/LoginPage.ui
                    GUI/SignupPage/SignupPage.hpp
                    GUI/SignupPage/SignupPage.cpp
                    GUI/SignupPage/SignupPage.ui
                    GUI/MainPage/MainPage.hpp
                    GUI/MainPage/MainPage.cpp
                    GUI/MainPage/MainPage.ui
                    GUI/RoomPage/RoomPage.hpp
                    GUI/RoomPage/RoomPage.cpp
                    GUI/RoomPage/RoomPage.ui
                    GUI/RoomCreationPage/RoomCreationPage.hpp
                    GUI/RoomCreationPage/RoomCreationPage.cpp
                    GUI/RoomCreationPage/RoomCreationPage.ui
                    GUI/RoomSearchPage/RoomSearchPage.hpp
                    GUI/RoomSearchPage/RoomSearchPage.cpp
                    GUI/RoomSearchPage/RoomSearchPage.ui
                    GUI/MCLineEdit/MCLineEdit.cpp
                    GUI/MCLineEdit/mclineedit.h)

add_executable(client main.cpp
                      AppController/AppController.cpp
                      ${ACCOUNT_SOURCES}
                      ${ROOM_SOURCES}
                      ${NETWORK_SOURCES}
                      ${UI_SOURCES})

target_link_libraries(client PRIVATE Qt5::Widgets
                                     Qt5::Network
                                     Qt5::Core)



install(TARGETS client
                LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})