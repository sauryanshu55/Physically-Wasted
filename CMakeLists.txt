cmake_minimum_required(VERSION 3.18)

project(nbody C)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
set(INC_DIR ${CMAKE_SOURCE_DIR}/include)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall -Wextra -Wpedantic -Werror")

if(WIN32)
    set(LIB_SUFFIX ".dll")
elseif(UNIX)
    set(LIB_SUFFIX ".so")
endif()

enable_testing()

include_directories(${INC_DIR})

add_subdirectory(${SRC_DIR})
add_subdirectory(${TEST_DIR})
