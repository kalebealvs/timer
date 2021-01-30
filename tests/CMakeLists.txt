
set(This TimerTests)
set(TESTS_SRC
    TimerId.cpp
    Duration.cpp
    ValidTimer.cpp
)

add_executable(${This} ${TESTS_SRC})
target_link_libraries(${This} PUBLIC
    gtest_main
    timer
)

include(GoogleTest)
gtest_add_tests(TARGET ${This})
