cmake_minimum_required(VERSION 3.18)

project(nbody C)

# Set the source files
set(SOURCE_FILE nbody.c)
set(EXECUTABLE_NAME nbody.out)
set(LIBRARY_NAME nbody)

# Add the shared library
add_library(${LIBRARY_NAME} SHARED ${SOURCE_FILE})

# Compile flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -fopenmp\
                                    -Wall -Wextra -Wpedantic -Werror \
                                    -Wshadow -Wstrict-prototypes \
                                    -Wold-style-definition -std=c99")

# Set library suffix based on platform
if(WIN32)
    set_target_properties(${LIBRARY_NAME} PROPERTIES SUFFIX ".dll")
elseif(UNIX)
    set_target_properties(${LIBRARY_NAME} PROPERTIES SUFFIX ".so")
endif()

# Set the library output directory
set_target_properties(${LIBRARY_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
)

# Add executable for main.c
add_executable(${EXECUTABLE_NAME} main.c)

# Link the nbody library to the executable
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${LIBRARY_NAME})

# Set executable output directory
set_target_properties(${EXECUTABLE_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)
