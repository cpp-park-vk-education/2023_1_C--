add_library(room src/RoomNetwork.cpp
                 src/RoomReplyHandler.cpp
                 src/RoomUseCase.cpp
                 src/RoomSwitcher.cpp)

target_include_directories(room PUBLIC include)

include_directories(../account/include)
include_directories(../network_manager/include)
include_directories(../controller/include)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()
