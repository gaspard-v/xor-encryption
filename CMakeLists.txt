cmake_minimum_required(VERSION 3.0.0)
project(xor-encryption VERSION 0.1.0)

set(SRCS
    base64_utils.c 
    conversion_utils.c 
    display_utils.c 
    hash_map.c 
    option.c 
    random_utils.c 
    simple_linked_list.c 
    xor_cipher.c
    file_io.c
    main.c)

set(HEADERS
    base64_utils.h 
    conversion_utils.h 
    display_utils.h 
    hash_map.h 
    option.h
    random_utils.h
    simple_linked_list.h
    file_io.h
    xor_cipher.h)

set(GCC_COVERAGE_COMPILE_FLAGS -mrdrnd -Werror=vla -pedantic-errors -Werror -Wall -Wextra -Wno-unused-parameter)
set(GCC_DEBUG_FLAGS -O0)
set(GCC_RELEASE_FLAGS -03)

set(MSVC_DEBUG_FLAGS /Od /DEBUG /INCREMENTAL /Wall)
set(MSVC_RELEASE_FLAGS /O2 /DNDEBUG /Gy /Wall)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(${GCC_COVERAGE_COMPILE_FLAGS})
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(${GCC_DEBUG_FLAGS})
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(${GCC_RELEASE_FLAGS})
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(${MSVC_DEBUG_FLAGS})
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(${MSVC_DEBUG_FLAGS})
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    endif()
endif()
add_executable(${PROJECT_NAME} ${SRCS} ${HEADERS})

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)