cmake_minimum_required(VERSION 3.6.0 FATAL_ERROR) 

find_program( MEMORYCHECK_COMMAND valgrind )
set( MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full --error-exitcode=1" )

get_filename_component(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.. ABSOLUTE)
get_filename_component(ANTLR_DIR ${ROOT_DIR}/libs/antlr4 ABSOLUTE)


project(rtamt-tests)
include (CTest)
add_subdirectory(../source rtamt EXCLUDE_FROM_ALL)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_EXTENSIONS OFF)

include_directories(SYSTEM "${ROOT_DIR}/source")
include_directories(SYSTEM ${ANTLR_DIR}/runtime/src)

if ("$ENV{CODE_COVERAGE}" STREQUAL "ON")
    add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
    set(CMAKE_EXE_LINKER_FLAGS "-fprofile-instr-generate -fcoverage-mapping")
endif ("$ENV{CODE_COVERAGE}" STREQUAL "ON")

# keep cache clean
# https://cliutils.gitlab.io/modern-cmake/chapters/testing/googletest.html
mark_as_advanced(
    BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
    gmock_build_tests gtest_build_samples gtest_build_tests
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)


enable_testing()
include(GoogleTest)

################################
# Unit Tests
################################
# Add test cpp file
# add_executable( test-example test-example.cpp )
# Link test executable against gtest & gtest_main
# target_link_libraries(test-example gmock gtest gtest_main pthread)
# add_test( test-example test-example )

macro(package_add_test TESTNAME)
    # create an exectuable in which the tests will be stored
    add_executable(${TESTNAME} ${ARGN})
    # link the Google test infrastructure, mocking library, and a default main fuction to
    # the test executable.  Remove g_test_main if writing your own main function.
    target_link_libraries(${TESTNAME} gtest gmock gtest_main pthread rtamt)
    # gtest_discover_tests replaces gtest_add_tests,
    # see https://cmake.org/cmake/help/v3.10/module/GoogleTest.html for more options to pass to it
    gtest_discover_tests(${TESTNAME}
        # set a working directory so your project root so that you can find test data via paths relative to the project root
        WORKING_DIRECTORY ${ROOT_DIR}/bin
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${ROOT_DIR}/bin"
    )
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

package_add_test(test_node_structure           node/test_node_structure.cpp)
package_add_test(test_node_evaluation          node/test_node_evaluation.cpp)
package_add_test(test-example                  test-example.cpp)
package_add_test(test_stl_pastification        spec/test_stl_pastification.cpp)
package_add_test(test_stl_evaluation           spec/test_stl_evaluation.cpp)
package_add_test(test_stl_reset_monitor_state  spec/test_stl_reset_monitor_state.cpp)
package_add_test(test_stl_specification_parser spec/test_stl_specification_parser.cpp)
package_add_test(test_stl_specification        rtamt/test_stl_specification.cpp)
package_add_test(test_time_units               spec/test_time_units.cpp)
package_add_test(test_parser_coverage          spec/test_parser_coverage.cpp)

