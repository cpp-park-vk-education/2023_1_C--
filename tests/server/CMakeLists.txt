project (server_test)

include_directories(server ../../server/include ./mocks/include)

add_executable(server_test tests.cpp)

target_link_libraries(server_test gtest gmock)

gtest_discover_tests(server_test)