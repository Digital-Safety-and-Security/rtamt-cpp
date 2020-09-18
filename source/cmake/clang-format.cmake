# Get all project files
file(GLOB_RECURSE
     ALL_CXX_SOURCE_FILES
     *.cpp *.hpp
     )

# Adding clang-format target if executable is found
find_program(CLANG_FORMAT "clang-format-7")
if(CLANG_FORMAT)
  add_custom_target(
    format
    COMMAND ${CLANG_FORMAT}
    -i
    -style=file
    ${ALL_CXX_SOURCE_FILES}
    )
endif()
