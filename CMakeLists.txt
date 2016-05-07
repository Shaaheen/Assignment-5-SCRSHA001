cmake_minimum_required(VERSION 3.3)
project(Assignment_5_SCRSHA001)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Audio.h test/AudioUnitTests.cpp)
add_executable(Assignment_5_SCRSHA001 ${SOURCE_FILES})