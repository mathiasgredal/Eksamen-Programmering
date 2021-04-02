cmake_minimum_required(VERSION 3.14)

## Configure Compiler
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(BUILD_SHARED_LIBS TRUE)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

## CMake Extensions
include(./cmake/CMakeRC.cmake)
include(./cmake/CPM.cmake)

## Create project
project(Eksamen LANGUAGES CXX)

## Dependencies
CPMAddPackage(
  NAME glfw
  GITHUB_REPOSITORY glfw/glfw
  GIT_TAG 3.3.3
  OPTIONS "GLFW_BUILD_DOCS OFF" "GLFW_BUILD_TESTS OFF" "GLFW_BUILD_EXAMPLES OFF"
)
CPMAddPackage(
  NAME bgfx
  GITHUB_REPOSITORY widberg/bgfx.cmake
  GIT_TAG 66f18daf5c380b34f4745ac0922b8a9853b51ad9
  OPTIONS "BGFX_LIBRARY_TYPE SHARED"
)
CPMAddPackage(
  NAME imgui_src
  GITHUB_REPOSITORY ocornut/imgui
  VERSION 1.82
)
CPMAddPackage(
  NAME fmt
  GITHUB_REPOSITORY fmtlib/fmt
  GIT_TAG 7.1.3
)
CPMAddPackage(
  NAME cxxopts
  GITHUB_REPOSITORY jarro2783/cxxopts
  VERSION 2.2.1
)

## Libraries
add_library(imgui
    "${bgfx_SOURCE_DIR}/bgfx/examples/common/imgui/imgui.cpp"
    "${imgui_src_SOURCE_DIR}/backends/imgui_impl_glfw.cpp")
target_include_directories(imgui PUBLIC
    "${bgfx_SOURCE_DIR}/bgfx/examples/common/imgui"
    "${imgui_src_SOURCE_DIR}/backends")
target_link_libraries(imgui dear-imgui bgfx glfw) # We link the main part of imgui source code from bgfx

add_library(nanovg
    "${bgfx_SOURCE_DIR}/bgfx/examples/common/nanovg/nanovg.cpp"
    "${bgfx_SOURCE_DIR}/bgfx/examples/common/nanovg/nanovg_bgfx.cpp")
target_include_directories(nanovg PUBLIC
    "${bgfx_SOURCE_DIR}/bgfx/examples/common/nanovg"
    "${bgfx_SOURCE_DIR}/bgfx/3rdparty")
target_link_libraries(nanovg bgfx)

## Targets
add_executable(demo "src/main.cpp"
    "src/App.cpp" "include/App.h")
target_link_libraries(demo glfw bgfx imgui nanovg fmt cxxopts)

