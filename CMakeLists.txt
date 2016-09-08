cmake_minimum_required(VERSION 3.6)
project(cs430_proj1_images)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c header.c header.h helpers.c helpers.h ppm3.c ppm3.h)
add_executable(cs430_proj1_images ${SOURCE_FILES})