if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    list(
        APPEND
        GENERAL_CXX_FLAGS
        -Weverything
        -Wno-c++98-compat
        -Wno-c++98-compat-pedantic
        -Wno-c++98-c++11-compat-pedantic
        -Wno-ctad-maybe-unsupported
        -Wno-c++-compat
        -Wno-unused-const-variable
        -Wno-format-nonliteral
        -Wno-global-constructors
        -Wno-exit-time-destructors
    )

    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "15")
        list(APPEND GENERAL_CXX_FLAGS -Wlifetime)
    endif()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lc++abi")
    set(ADDRESS_SAN
        -fsanitize=address
        -fno-omit-frame-pointer
        -fsanitize-address-use-after-return=always
        -fsanitize-address-use-after-scope
        -fno-optimize-sibling-calls
    )
    set(UNDEF_SAN
        -fsanitize=undefined,float-divide-by-zero,unsigned-integer-overflow,implicit-conversion,local-bounds,array-bounds,nullability,implicit-integer-truncation,implicit-integer-arithmetic-value-change,implicit-conversion,integer
    )
    set(ADDRESS_UNDEF_SAN
        -fsanitize=address,undefined,float-divide-by-zero,unsigned-integer-overflow,implicit-conversion,local-bounds,array-bounds,nullability,implicit-integer-truncation,implicit-integer-arithmetic-value-change,implicit-conversion,integer
        -fno-omit-frame-pointer
        -fsanitize-address-use-after-return=always
        -fsanitize-address-use-after-scope
        -fno-optimize-sibling-calls
    )
    set(MEMORY_SAN
        -fsanitize=memory
        -fsanitize-memory-track-origins
        -fno-omit-frame-pointer
        -fno-optimize-sibling-calls
        -fsanitize-memory-use-after-dtor
    )
    set(THREAD_SAN -fsanitize=thread)

elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    list(
        APPEND
        GENERAL_CXX_FLAGS
        -Wduplicated-cond
        -Wduplicated-branches
        -Wlogical-op
        -Wuseless-cast
        -Wreorder
        -fanalyzer
    )

    set(ADDRESS_SAN -fsanitize=leak,address)
    set(UNDEF_SAN -fsanitize=undefined,pointer-compare,pointer-subtract)
    set(ADDRESS_UNDEF_SAN
        -fsanitize=leak,undefined,address,pointer-compare,pointer-subtract
    )
    set(MEMORY_SAN
        -fsanitize=memory
        -fsanitize-memory-track-origins
        -fno-omit-frame-pointer
        -fno-optimize-sibling-calls
        -fsanitize-memory-use-after-dtor
    )
    set(THREAD_SAN -fsanitize=thread)
endif()
