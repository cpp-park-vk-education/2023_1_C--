project (server_test)

set(INC_DIR ../../server/include)

include_directories(server ${INC_DIR} ${INC_DIR}/HttpRequest ./mocks/include)

add_executable(server_test tests.cpp)

target_link_libraries(server_test gtest gmock)

gtest_discover_tests(server_test)