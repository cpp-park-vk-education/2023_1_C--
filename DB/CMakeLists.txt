cmake_minimum_required(VERSION 3.14)

project(DB LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 REQUIRED COMPONENTS Core Sql)

include_directories(
  include
)

set(SRC
  src/DBManager.cpp
  src/ClientDBManager.cpp
  src/RoomDBManager.cpp
  src/Client.cpp
  src/Room.cpp 
  src/Message.cpp
)

add_library(DB include ${SRC})

target_link_libraries(DB PRIVATE Qt5::Core Qt5::Sql)

install(TARGETS DB
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})