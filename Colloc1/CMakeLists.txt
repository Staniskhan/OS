cmake_minimum_required(VERSION 3.12)

project(Colloc1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(tasks)
include_directories(dependencies)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/executables)

add_executable(
  task1
  tasks/task1.cpp
)

add_executable(
  task2
  tasks/task2.cpp
)

add_executable(
  task3
  tasks/task3.cpp
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
	tests1
	tests/tests_task1.cpp
)

add_executable(
	tests2
	tests/tests_task2.cpp
)

add_executable(
	tests3
	tests/tests_task3.cpp
)
	
target_link_libraries(
  tests1
  PRIVATE
  GTest::gtest_main
)

target_link_libraries(
  tests2
  PRIVATE
  GTest::gtest_main
)

target_link_libraries(
  tests3
  PRIVATE
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests1)
gtest_discover_tests(tests2)
gtest_discover_tests(tests3)