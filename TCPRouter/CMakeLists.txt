cmake_minimum_required(VERSION 3.14)

project(TCPRouter LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 REQUIRED COMPONENTS Core Network)
include_directories(
  include
)

set(SRC
  src/TCPMessageRouter.cpp
  main.cpp
)

add_executable(TCPRouter ${SRC})

target_link_libraries(TCPRouter Qt5::Core Qt5::Network)

install(TARGETS TCPRouter
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})