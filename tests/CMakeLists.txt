cmake_minimum_required(VERSION 3.13.4)
project(tests)

find_package(GTest REQUIRED)

add_subdirectory(server) #project <name>_test

# add_subdirectory(client)