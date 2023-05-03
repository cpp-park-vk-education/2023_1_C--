cmake_minimum_required(VERSION 3.14)

project(DB LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)

include_directories(
  include
  src
)

add_executable(DB
  src/dbmanager.cpp
  src/clientdbmanager.cpp
  src/roomdbmanager.cpp
)

install(TARGETS DB
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
