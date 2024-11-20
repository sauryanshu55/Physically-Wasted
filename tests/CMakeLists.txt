add_library(tests INTERFACE)
target_precompile_headers(tests INTERFACE test.h)

function(add_nbody_test TEST_NAME SOURCE_FILE)
  add_executable(${TEST_NAME} ${SOURCE_FILE})
  target_include_directories(${TEST_NAME} PRIVATE ${INC_DIR})
  target_link_libraries(${TEST_NAME} PRIVATE tests)
  add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

add_nbody_test(nbody_test_example example.c)
