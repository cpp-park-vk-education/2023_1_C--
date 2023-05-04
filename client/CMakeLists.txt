option(BUILD_TESTS "build tests")

if(BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)

    add_compile_options(--coverage)
    add_link_options(--coverage)
endif()

add_subdirectory(lib/account)

# find_package(Qt6 REQUIRED COMPONENTS Widgets Network Core)
# target_link_libraries(account PRIVATE Qt6::Widgets Qt6::Network Qt6::Core)
