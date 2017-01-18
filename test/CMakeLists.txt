add_executable(big_test main.cpp)
target_link_libraries(big_test libbig)
set_property(TARGET big_test PROPERTY CXX_STANDARD 14)
add_custom_command(TARGET big_test POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_CURRENT_SOURCE_DIR}/files $<TARGET_FILE_DIR:big_test>)