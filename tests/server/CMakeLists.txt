project (server_test)

set(MAIN_DIR ../../server)

set(SERVICES_DIR ../../server/Services)

include_directories(
    ${MAIN_DIR}/HttpRequest
    ${MAIN_DIR}/HttpResponse
    ${MAIN_DIR}/HttpListener
    ${MAIN_DIR}/HttpHandlers
    ${MAIN_DIR}/HttpControllers
    ${MAIN_DIR}/DbInterface
    ${MAIN_DIR}/Services
    ${SERVICES_DIR}/CreateRoomService
    ${SERVICES_DIR}/DeleteRoomService
    ${SERVICES_DIR}/JoinRoomService
    ${SERVICES_DIR}/LoginService
    ${SERVICES_DIR}/SendMessageService
    ${SERVICES_DIR}/GetNewMessageService
    ./mocks/include)

add_executable(server_test
    tests.cpp
    ${MAIN_DIR}/HttpHandlers/HttpRequestMapper.cpp
    ${SERVICES_DIR}/CreateRoomService/CreateRoomService.cpp
    ${SERVICES_DIR}/DeleteRoomService/DeleteRoomService.cpp
    ${SERVICES_DIR}/JoinRoomService/JoinRoomService.cpp
    ${SERVICES_DIR}/LoginService/LoginService.cpp
    ${SERVICES_DIR}/SendMessageService/SendMessageService.cpp
    ${SERVICES_DIR}/GetNewMessageService/GetNewMessageService.cpp
    )

target_link_libraries(server_test gtest gmock)

gtest_discover_tests(server_test)