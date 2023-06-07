cmake_minimum_required(VERSION 3.14)

project(DB_tests LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

add_executable(DB_tests
  test.cpp
)

target_link_libraries(DB_tests gtest gmock)

install(TARGETS DB_tests
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})