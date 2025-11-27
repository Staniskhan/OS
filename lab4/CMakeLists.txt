cmake_minimum_required(VERSION 3.15)
project(Lab4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(includes)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/executables)

add_executable(Receiver src/Receiver.cpp)
add_executable(Sender src/Sender.cpp)

target_link_libraries(Receiver PRIVATE kernel32)
target_link_libraries(Sender PRIVATE kernel32)

add_executable(tests tests/test.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
	
target_link_libraries(
  tests
  PRIVATE
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
