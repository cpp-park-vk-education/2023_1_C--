add_library(account src/AccountNetwork.cpp
                    src/AccountReplyHandler.cpp
                    src/AccountUseCase.cpp
                    src/AccountSwitcher.cpp
                    src/Forms.cpp)
target_include_directories(account PUBLIC include)

include_directories(../network_manager/include)
# include_directories(../room/include)
include_directories(../controller/include)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()
