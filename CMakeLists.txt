cmake_minimum_required(VERSION 3.8.0)

project(Timer VERSION 0.6.2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -O3")

include(cmake/flags.cmake)
include(cmake/compiler_specific.cmake)
include(cmake/sanitizer.cmake)
include(cmake/googletest.cmake)

include_directories(include)

add_subdirectory(src)

include(cmake/export.cmake)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
