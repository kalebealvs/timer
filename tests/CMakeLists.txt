include(CTest)
enable_testing()

set(This TimerTests)
set(TESTS_SRC TimerId.cpp Duration.cpp ValidTimer.cpp)

add_executable(${This} ${TESTS_SRC})
target_link_libraries(${This} PUBLIC gmock_main ${PROJECT_NAME})

target_compile_options(${This} PRIVATE ${PROJECT_CXX_FLAGS})
target_link_options(${This} PRIVATE ${GENERAL_CXX_LINK_FLAGS})

gtest_add_tests(TARGET ${This})
