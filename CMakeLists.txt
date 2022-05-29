cmake_minimum_required(VERSION 3.8.0)

project(Timer VERSION 0.6.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -O3")

include(cmake/flags.cmake)
include(cmake/compiler_specific.cmake)
include(cmake/sanitizer.cmake)
include(cmake/googletest.cmake)

include_directories(include)

add_library(${PROJECT_NAME} SHARED src/timer.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE ${GENERAL_CXX_FLAGS})
target_link_options(${PROJECT_NAME} PRIVATE ${GENERAL_CXX_LINK_FLAGS})

target_include_directories(
    ${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

include(cmake/export.cmake)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
