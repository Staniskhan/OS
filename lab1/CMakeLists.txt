cmake_minimum_required(VERSION 3.10)
project(lab1 LANGUAGES CXX)

add_executable(Main Main.cpp)
add_executable(Creator Creator.cpp)
add_executable(Reporter Reporter.cpp)

target_link_libraries(Main kernel32)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/build)
