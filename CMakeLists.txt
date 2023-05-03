cmake_minimum_required(VERSION 3.13.4)
project(teamgram)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(DB)

enable_testing()

add_subdirectory(tests)
