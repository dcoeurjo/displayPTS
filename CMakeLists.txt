cmake_minimum_required(VERSION 3.11.0)
project(displayPTS)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(polyscope)

add_executable(displayPTS main.cpp)
target_link_libraries(displayPTS polyscope)
