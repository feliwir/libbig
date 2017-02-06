add_executable(big_util main.cpp)
target_link_libraries(big_util libbig)
target_include_directories(big_util PRIVATE ${LIBBIG_ROOT}/deps/cxxopts/include)
set_property(TARGET big_util PROPERTY CXX_STANDARD 14)
add_custom_command(TARGET big_util POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_CURRENT_SOURCE_DIR}/files $<TARGET_FILE_DIR:big_util>)