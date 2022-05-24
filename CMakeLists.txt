cmake_minimum_required(VERSION 3.8.0)

project(Timer VERSION 0.6.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include(cmake/flags.cmake)
include(cmake/compiler_specific.cmake)
include(cmake/sanitizer.cmake)
include(cmake/googletest.cmake)

include_directories(include)

add_library(timer SHARED src/timer.cpp)
target_compile_options(timer PRIVATE ${GENERAL_CXX_FLAGS})
target_link_options(timer PRIVATE ${GENERAL_CXX_LINK_FLAGS})

if(BUILD_TEST)
    add_subdirectory(tests)
endif(BUILD_TEST)
