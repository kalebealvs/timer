cmake_minimum_required(VERSION 3.8.0)

project(Timer VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

enable_testing()

add_subdirectory(lib/googletest)

include_directories (include)

add_library(timer SHARED src/timer.cpp)

add_subdirectory(tests)