cmake_minimum_required(VERSION 3.10)
project(lab2 LANGUAGES CXX)

add_executable(Main lab2.cpp)

target_link_libraries(Main kernel32)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/build)
