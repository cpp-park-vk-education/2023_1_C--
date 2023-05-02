add_executable(TestAccountUseCase src/TestAccountUseCase.cpp)

add_executable(TestForms src/TestForms.cpp)

add_executable(TestAccountNetwork src/TestAccountNetwork.cpp)

add_executable(TestAccountReplyHandler src/TestAccountReplyHandler.cpp)

target_link_libraries(TestAccountUseCase account
                                         GTest::gtest_main
                                         GTest::gmock)

target_link_libraries(TestAccountNetwork account
                                         GTest::gtest_main
                                         GTest::gmock)

target_link_libraries(TestAccountReplyHandler account
                                              GTest::gtest_main
                                              GTest::gmock)


target_link_libraries(TestForms account
                                 GTest::gtest_main)


                                   
add_test(TestAccountUseCase TestAccountUseCase)

add_test(TestAccountNetwork TestAccountNetwork)

add_test(TestAccountReplyHandler TestAccountReplyHandler)

add_test(TestForms TestForms)
