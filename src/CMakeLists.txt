add_library(${PROJECT_NAME} SHARED timer.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE ${GENERAL_CXX_FLAGS})
target_link_options(${PROJECT_NAME} PRIVATE ${GENERAL_CXX_LINK_FLAGS})

target_include_directories(
    ${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
