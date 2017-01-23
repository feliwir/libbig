add_executable(bigutil main.cpp)
target_link_libraries(bigutil libbig)
set_property(TARGET bigutil PROPERTY CXX_STANDARD 14)
add_custom_command(TARGET bigutil POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_CURRENT_SOURCE_DIR}/files $<TARGET_FILE_DIR:bigutil>)