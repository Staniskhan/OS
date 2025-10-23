cmake_minimum_required(VERSION 3.12)

project(lab2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/executables)

add_executable(
  Main
  src/lab2WinAPI.cpp
)

add_executable(
  MainThread
  src/lab2Thread.cpp
)

target_link_libraries(
	Main
	kernel32
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
	Tests
	tests/test_lab2.cpp
)

	
target_link_libraries(
  Tests
  PRIVATE
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(Tests)