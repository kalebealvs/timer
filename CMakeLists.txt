cmake_minimum_required(VERSION 3.8.0)

project(Timer VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(PROJECT_CXX_FLAGS -Wall -Wextra -Wshadow -Werror -Wpedantic)

enable_testing()

add_subdirectory(lib/googletest)

include_directories (include)

add_library(timer SHARED src/timer.cpp)
target_compile_options(timer PRIVATE ${PROJECT_CXX_FLAGS})

add_subdirectory(tests)