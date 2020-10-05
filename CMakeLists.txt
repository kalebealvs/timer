cmake_minimum_required(VERSION 3.8.0)

project(Timer VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

add_subdirectory(lib/googletest)

include_directories (include)

add_library(timer SHARED src/timer.cpp)

add_subdirectory(tests)