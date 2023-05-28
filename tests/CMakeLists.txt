find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(boolean_minimizer_tests
    test.cpp
    ../booleanminimizer.cpp
)

target_link_libraries(boolean_minimizer_tests
    Qt${QT_VERSION_MAJOR}::Widgets
    GTest::gtest_main
    gmock_main
)

include(GoogleTest)
gtest_discover_tests(boolean_minimizer_tests)
