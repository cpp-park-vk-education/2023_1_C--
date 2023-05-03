cmake_minimum_required(VERSION 3.13.4)
project(teamgram)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(server)

# add_subdirectory(client)

enable_testing()

add_subdirectory(tests)
