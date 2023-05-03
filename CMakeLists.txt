cmake_minimum_required(VERSION 3.13.4)
project(teamgram)

set(CMAKE_CXX_STANDARD 17)

include_directories(DB)

add_subdirectory(DB)

add_subdirectory(tests)