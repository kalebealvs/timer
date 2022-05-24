set(GENERAL_CXX_FLAGS
    -Wall
    -Wextra
    -Wshadow
    -Wpedantic
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Wunused
    -Wundef
    -Woverloaded-virtual
    -Wcast-align
    -Wconversion
    -Wsign-conversion
    -Wmisleading-indentation
    -Wdouble-promotion
    -Wnull-dereference
    -Winvalid-pch
    -Wmissing-include-dirs
    -Wuninitialized
    -Wold-style-cast
    -Wstack-protector
    -fstack-protector
    -Wformat=2
    -fno-common
    -Wzero-as-null-pointer-constant
    -Wctor-dtor-privacy
    -Wstrict-aliasing
    -fPIC
    -march=native
    -mtune=native
)

if(PROFILE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
endif()

set(DBG_BUILD_TYPES RelWithDebInfo Debug)
if(${CMAKE_BUILD_TYPE} IN_LIST DBG_BUILD_TYPES)
    set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -fdata-sections -ffunction-sections -fstack-usage"
    )
endif()
