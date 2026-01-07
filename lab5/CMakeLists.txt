cmake_minimum_required(VERSION 3.15)
project(lab5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(includes)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/executables)

add_executable(Client src/Client.cpp)
add_executable(Server src/Server.cpp)

target_link_libraries(Client PRIVATE kernel32)
target_link_libraries(Server PRIVATE kernel32)

# add_executable(tests tests/test.cpp)