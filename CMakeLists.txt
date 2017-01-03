cmake_minimum_required(VERSION 3.1)

project(libbig CXX C)

add_subdirectory(src)

option(BUILD_TEST "List of all files inside a big archive" ON)
if(BUILD_TEST)
	add_subdirectory(test)
endif()