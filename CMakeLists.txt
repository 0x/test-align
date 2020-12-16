cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(test_align)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(HEADERS
	include/task1.hpp
	include/task2.hpp
	include/task3.hpp
)

set(SOURCES
	src/task1.cpp
	src/task2.cpp
	src/task3.cpp
)

add_library(core ${HEADERS} ${SOURCES})

target_compile_options(core PRIVATE
     $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
          -Wall>
     $<$<CXX_COMPILER_ID:MSVC>:
          /W4>)
target_include_directories(core PUBLIC include)

add_executable(task1  src/main1.cpp)
target_link_libraries(task1 PRIVATE core)

add_executable(task2 src/main2.cpp)
target_link_libraries(task2 PRIVATE core)

add_executable(task3 src/main3.cpp)
target_link_libraries(task3 PRIVATE core)

option(ENABLE_TESTS "Enable tests" ON)
if (${ENABLE_TESTS})
	message(STATUS "Building with tests")
    	enable_testing()
	add_subdirectory(googletest)
	add_subdirectory(test)
endif()


