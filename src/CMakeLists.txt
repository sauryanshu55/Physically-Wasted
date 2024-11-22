set(SOURCE_FILE ${SRC_DIR}/nbody.c ${SRC_DIR}/bh.c)
set(EXECUTABLE_NAME nbody.out)
set(LIBRARY_NAME nbody)

# Create a shared library
add_library(${LIBRARY_NAME} SHARED ${SOURCE_FILE})
set_target_properties(${LIBRARY_NAME} PROPERTIES
    SUFFIX ${LIB_SUFFIX}
    LIBRARY_OUTPUT_DIRECTORY ${LIB_DIR}
)

# Create an executable
add_executable(${EXECUTABLE_NAME} ${SRC_DIR}/main.c)

# Link the executable to the library and the math library in a single call
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${LIBRARY_NAME} m)

# Set the output directory for the executable
set_target_properties(${EXECUTABLE_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
)
