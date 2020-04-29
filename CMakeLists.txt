cmake_minimum_required(VERSION 3.12)
project(Chess)

set(CMAKE_CXX_STANDARD 14)

add_executable(Chess main.cpp)

add_subdirectory(Google_tests)
