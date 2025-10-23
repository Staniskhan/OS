cmake_minimum_required(VERSION 3.10)
project(Lab3)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
include_directories(src)

add_executable(Main src/Main.cpp src/functions.cpp)

# add_executable(Tests tests/Tests.cpp src/functions.cpp)

target_link_libraries(Main PRIVATE kernel32)
# target_link_libraries(Tests PRIVATE kernel32)
#[[
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1
)

FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(Tests)

target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain)
]]