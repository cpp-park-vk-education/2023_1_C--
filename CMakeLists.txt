cmake_minimum_required(VERSION 3.13.4)
project(teamgram)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(DB)

add_subdirectory(DB)

add_subdirectory(server)

# add_subdirectory(client)

# add_subdirectory(tests)

# enable_testing()
