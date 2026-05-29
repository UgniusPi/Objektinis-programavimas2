cmake_minimum_required(VERSION 3.14)
project(studentas_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# Require GoogleTest to be available (recommend using vcpkg toolchain)
find_package(GTest CONFIG REQUIRED)

add_executable(studentas_gtest
  test_studentas_gtest.cpp
  studentas.cpp
)

target_include_directories(studentas_gtest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(studentas_gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(studentas_gtest)
