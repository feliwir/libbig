cmake_minimum_required(VERSION 3.1)

project(libbig CXX C)

set(LIBBIG_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(src)

option(LIBBIG_BUILD_TOOLS "Build tools using libbig" ON)
if(LIBBIG_BUILD_TOOLS)
	add_subdirectory(tools)
endif()