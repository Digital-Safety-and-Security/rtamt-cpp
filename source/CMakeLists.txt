cmake_minimum_required(VERSION 3.6.0 FATAL_ERROR) 

get_filename_component(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.. ABSOLUTE)
get_filename_component(ANTLR_DIR ${ROOT_DIR}/libs/antlr4 ABSOLUTE)

project(rtamt)

set(WITH_LIBCXX Off CACHE BOOL "Disable LIBCXX")

add_subdirectory(${ANTLR_DIR} ${CMAKE_CURRENT_BINARY_DIR}/antlr4 )
include_directories(SYSTEM ${ANTLR_DIR}/runtime/src)
set(ANTLR_LIBRARIES antlr4_static uuid)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wextra -Wno-unsequenced -Wreorder -Wuninitialized -Wswitch -Wold-style-cast -Wno-unused-parameter")

# own header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if ("$ENV{CODE_COVERAGE}" STREQUAL "ON")
    add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
    set(CMAKE_EXE_LINKER_FLAGS "-fprofile-instr-generate -fcoverage-mapping")
endif ("$ENV{CODE_COVERAGE}" STREQUAL "ON")

# Including custom cmake rules
include(cmake/clang-format.cmake)
include(cmake/clang-tidy.cmake)

add_library(sources OBJECT
  rtamt/stl_specification.cpp
  spec/stl_inner_specification.cpp
  node/stl_node.cpp
  node/stl_not_node.cpp
  node/stl_abs_node.cpp
  node/stl_addition_node.cpp
  node/stl_always_node.cpp
  node/stl_combinatorial_binary_node.cpp
  node/stl_constant_node.cpp
  node/stl_division_node.cpp
  node/stl_eventually_node.cpp
  node/stl_fall_node.cpp
  node/stl_historically_bounded_node.cpp
  node/stl_historically_node.cpp
  node/stl_once_bounded_node.cpp
  node/stl_once_node.cpp
  node/stl_precedes_bounded_node.cpp
  node/stl_until_bounded_node.cpp
  node/stl_predicate_node.cpp
  node/stl_rise_node.cpp
  node/stl_since_bounded_node.cpp
  node/stl_since_node.cpp
  node/stl_subtraction_node.cpp
  node/stl_always_bounded_node.cpp
  node/stl_eventually_bounded_node.cpp
  node/stl_variable_node.cpp
  node/stl_multiplication_node.cpp
  spec/stl_pastification.cpp
  spec/stl_evaluation.cpp
  spec/stl_inner_specification.cpp
  spec/stl_reset_monitor_state.cpp
  spec/stl_specification_parser.cpp

)

add_library(rtamt STATIC grammar/StlLexer.cpp
  grammar/StlParser.cpp
  grammar/StlParserBaseVisitor.cpp
  grammar/StlParserVisitor.cpp
  $<TARGET_OBJECTS:sources>)
  

target_link_libraries(rtamt ${ANTLR_LIBRARIES})

install(TARGETS rtamt ARCHIVE DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/rtamt
        DESTINATION include
        FILES_MATCHING PATTERN "*.hpp"
)
