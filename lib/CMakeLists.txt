cmake_minimum_required(VERSION 3.13.4)
project(teamgram)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    DB
    DB_tests
)

add_subdirectory(DB)

enable_testing()

add_subdirectory(DB_tests)