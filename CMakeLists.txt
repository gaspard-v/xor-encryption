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
    main.c)

set(HEADERS
    base64_utils.h 
    conversion_utils.h 
    display_utils.h 
    hash_map.h 
    option.h
    random_utils.h
    simple_linked_list.h 
    xor_cipher.h)

set(GCC_COVERAGE_COMPILE_FLAGS "-mrdrnd -Werror=vla -g")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
add_executable(${PROJECT_NAME} ${SRCS} ${HEADERS})

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)