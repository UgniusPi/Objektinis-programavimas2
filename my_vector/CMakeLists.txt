cmake_minimum_required(VERSION 3.14)
project(my_vector_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# Try to find GoogleTest (vcpkg config), otherwise fetch it via FetchContent
find_package(GTest CONFIG QUIET)
if (NOT GTest_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main
  )
  # For MSVC users: avoid overriding compiler flags
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
endif()

# GoogleTest for Vector implementation (tests and implementation are in this folder)
add_executable(vector_gtest
  test_vector_gtest.cpp
  Vector.cpp
)

target_include_directories(vector_gtest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(vector_gtest PRIVATE GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(vector_gtest)
