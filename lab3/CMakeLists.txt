cmake_minimum_required(VERSION 3.12)
project(Lab3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(includes)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/executables)

add_executable(Main src/Main.cpp)

# add_executable(MainThread src/MainThread.cpp)

target_link_libraries(Main PRIVATE kernel32)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1
)

FetchContent_MakeAvailable(Catch2)

add_executable(Tests tests/Tests.cpp)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

include(CTest)
include(Catch)
catch_discover_tests(Tests)

target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain)
