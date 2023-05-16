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
  
find_package(Qt6 REQUIRED COMPONENTS Widgets
                                     Network
                                     Core)

include_directories(
    Account/include
    Network/include  
    Room/include
    include
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(ACCOUNT_SOURCES Account/src/AccountNetwork.cpp
                    Account/src/AccountReplyHandler.cpp
                    Account/src/AccountSwitcher.cpp
                    Account/src/AccountUseCase.cpp
                    Account/src/Forms.cpp)

set(ROOM_SOURCES    Room/src/RoomNetwork.cpp
                    Room/src/RoomReplyHandler.cpp
                    Room/src/RoomSwitcher.cpp
                    Room/src/RoomUseCase.cpp
                    Room/include/IMainPageUi.hpp
                    Room/include/IRoomNetwork.hpp
                    Room/include/IRoomPageUi.hpp
                    Room/include/IRoomReplyHandler.hpp
                    Room/include/IRoomSwitcher.hpp
                    Room/include/IRoomUseCase.hpp
                    Room/include/IUserInfoUi.hpp
                    Room/include/RoomData.hpp
                    Room/include/RoomNetwork.hpp
                    Room/include/RoomReplyHandler.hpp
                    Room/include/RoomSwitcher.hpp
                    Room/include/RoomUseCase.hpp
                    src/MCLineEdit.cpp include/mclineedit.h)

set(NETWORK_SOURCES Network/src/NetworkManager.cpp
                    Network/src/Communication
                    Network/src/Serializer
                    Network/src/Deserializer)

SET(UI_SOURCES      include/MainWindow.hpp
                    src/MainWindow.cpp
                    src/MainWindow.ui
                    include/LoginPage.hpp
                    src/LoginPage.cpp
                    src/LoginPage.ui
                    include/SignupPage.hpp
                    src/SignupPage.cpp
                    src/SignupPage.ui
                    include/MainPage.hpp
                    src/MainPage.cpp
                    src/MainPage.ui
                    include/RoomPage.hpp
                    src/RoomPage.cpp
                    src/RoomPage.ui
                    include/RoomPage.hpp
                    src/RoomPage.cpp
                    src/RoomPage.ui
                    include/RoomCreationPage.hpp
                    src/RoomCreationPage.cpp
                    src/RoomCreationPage.ui
                    include/RoomSearchPage.hpp
                    src/RoomSearchPage.cpp
                    src/RoomSearchPage.ui)

add_executable(client src/main.cpp
                      src/AppController.cpp
                      ${ACCOUNT_SOURCES}
                      ${ROOM_SOURCES}
                      ${NETWORK_SOURCES}
                      ${UI_SOURCES})

target_link_libraries(client PRIVATE Qt6::Widgets
                                     Qt6::Network
                                     Qt6::Core)



install(TARGETS client
                LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})