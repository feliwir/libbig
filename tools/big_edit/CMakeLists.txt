set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find Qt Library
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)

add_executable(big_edit WIN32 main.cpp editor.cpp editor.hpp)

target_link_libraries(big_edit libbig Qt5::Widgets Qt5::Multimedia)
target_include_directories(big_edit PRIVATE)

set_property(TARGET big_edit PROPERTY CXX_STANDARD 14)

add_custom_command( TARGET big_edit POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_CURRENT_SOURCE_DIR}/../files $<TARGET_FILE_DIR:big_edit>)