cmake_minimum_required(VERSION 3.11.0)
project(displayPTS)

set(CMAKE_CXX_STANDARD 11 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(polyscope)

add_executable(displayPTS main.cpp)
target_link_libraries(displayPTS polyscope)
