cmake_minimum_required(VERSION 3.12)
project(Onegin)

set(CMAKE_CXX_STANDARD 17)

add_executable(Onegin src/main.cpp src/OneginSorter.h src/OneginSorter.cpp src/tests/test.cpp)

add_subdirectory(googletest-master)

include_directories(src/tests)
include_directories(googletest-master/googletest/include)
include_directories(googletest-master/googlemock/include)

target_link_libraries(Onegin gtest gtest_main)