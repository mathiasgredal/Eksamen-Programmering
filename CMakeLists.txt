cmake_minimum_required(VERSION 3.14)

project(Eksamen)

## Configure Compiler
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

## CMake Extensions
include(./cmake/CMakeRC.cmake)
include(./cmake/CPM.cmake)

## Dependencies

## Targets
add_executable(demo "src/main.cpp")


