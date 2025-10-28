cmake_minimum_required(VERSION 3.12)

project(Colloc1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(tasks)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/executables)

add_executable(
  task1
  tasks/task1.cpp
)