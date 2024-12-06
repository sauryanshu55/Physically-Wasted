add_library(tests INTERFACE)
target_precompile_headers(tests INTERFACE test.h)


set(LIBRARY_NAME testnbody)
set(SOURCE_FILE ${SRC_DIR}/nbody.c ${SRC_DIR}/bh.c)
add_library(${LIBRARY_NAME} SHARED ${SOURCE_FILE})
set_target_properties(${LIBRARY_NAME} PROPERTIES
    SUFFIX ${LIB_SUFFIX}
    LIBRARY_OUTPUT_DIRECTORY ${LIB_DIR}
)


function(add_nbody_test TEST_NAME SOURCE_FILE)
  add_executable(${TEST_NAME} ${SOURCE_FILE})
  target_include_directories(${TEST_NAME} PRIVATE ${INC_DIR})
  target_link_libraries(${TEST_NAME} PRIVATE tests ${LIBRARY_NAME} m)
  add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

add_nbody_test(nbody_test_example example.c)
add_nbody_test(nbody_test_twobody twobody.c)
add_nbody_test(nbody_test_getr getr.c)
