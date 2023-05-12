option(BUILD_TESTS "build tests")

if(BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)

    add_compile_options(--coverage)
    add_link_options(--coverage)
endif()

include_directories(
    Account/include  
    Controller/include  
    Network/include  
    Room/include 
)

add_executable(client src/main.cpp
                      src/AppController.cpp
                      Account/src/AccountNetwork.cpp
                      Account/src/AccountReplyHandler.cpp
                      Account/src/AccountSwitcher.cpp
                      Account/src/AccountUseCase.cpp
                      Account/src/Forms.cpp
                      Room/src/RoomNetwork.cpp
                      Room/src/RoomReplyHandler.cpp
                      Room/src/RoomSwitcher.cpp
                      Room/src/RoomUseCase.cpp)

# find_package(Qt6 REQUIRED COMPONENTS Widgets Network Core)
# target_link_libraries(account PRIVATE Qt6::Widgets Qt6::Network Qt6::Core)


if (BUILD_TESTS)
    add_subdirectory(Account/tests)
    # add_subdirectory(Room/tests)
endif()
