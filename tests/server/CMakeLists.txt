project (server_test)

set(MAIN_DIR ../../server)

include_directories(
    ${MAIN_DIR}/HttpRequest
    ${MAIN_DIR}/HttpRequest
    ${MAIN_DIR}/HttpResponse
    ${MAIN_DIR}/HttpListener
    ${MAIN_DIR}/HttpHandlers
    ${MAIN_DIR}/HttpControllers
    ./mocks/include)

add_executable(server_test tests.cpp)

target_link_libraries(server_test gtest gmock)

gtest_discover_tests(server_test)