cmake_minimum_required(VERSION 3.1)

project(libbig CXX C)

set(LIBBIG_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(src)

option(LIBBIG_BUILD_TEST "List of all files inside a big archive" ON)
if(LIBBIG_BUILD_TEST)
	add_subdirectory(test)
endif()