if (UNIX)
	if (DEFINED ENV{CLANG_TIDY})
		find_program(
		CLANG_TIDY_EXE
		NAMES "$ENV{CLANG_TIDY}"
		DOC "Path to clang-tidy executable"
		)
		if(NOT CLANG_TIDY_EXE)
		message(FATAL_ERROR "clang-tidy not found. Specified name of executable: $ENV{CLANG_TIDY}")
		else(NOT CLANG_TIDY_EXE)
		message(STATUS "Using clang-tidy for static analysis: ${CLANG_TIDY_EXE}")
		# Configuration moved to .clang-tidy file in the parent directory
		set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}"
		  # "-fix" "-fix-errors" # auto-fixes issues, use with care!
		)
		endif(NOT CLANG_TIDY_EXE)
	endif(DEFINED ENV{CLANG_TIDY})
endif (UNIX)
