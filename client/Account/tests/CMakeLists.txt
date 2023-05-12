include_directories(
    include
    ../include
)

add_executable(TestAccountUseCase src/TestAccountUseCase.cpp
                                  ../src/AccountUseCase.cpp)

add_executable(TestAccountNetwork src/TestAccountNetwork.cpp
                                  ../src/AccountNetwork.cpp)

add_executable(TestAccountReplyHandler src/TestAccountReplyHandler.cpp
                                       ../src/AccountReplyHandler.cpp)

add_executable(TestAccountSwitcher src/TestAccountSwitcher.cpp
                                   ../src/AccountSwitcher.cpp)

add_executable(TestForms src/TestForms.cpp
                         ../src/Forms.cpp)

target_link_libraries(TestAccountUseCase GTest::gtest_main
                                         GTest::gmock)

target_link_libraries(TestAccountNetwork GTest::gtest_main
                                         GTest::gmock)

target_link_libraries(TestAccountReplyHandler GTest::gtest_main
                                              GTest::gmock)

target_link_libraries(TestAccountSwitcher GTest::gtest_main
                                          GTest::gmock)

target_link_libraries(TestForms GTest::gtest_main)
                 
add_test(TestAccountUseCase TestAccountUseCase)
add_test(TestAccountNetwork TestAccountNetwork)
add_test(TestAccountReplyHandler TestAccountReplyHandler)
add_test(TestAccountSwitcher TestAccountSwitcher)
add_test(TestForms TestForms)
