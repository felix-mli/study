cmake_minimum_required(VERSION 3.10)
project(learn_gtest)

set(CMAKE_C_STANDARD 99)

add_subdirectory(tools/base)

# gtest demo
add_subdirectory(3rdparty/googletest)
add_subdirectory(demo/gtest)

# cjson demo
add_subdirectory(3rdparty/cJSON)
add_subdirectory(demo/cjson)

# socket demo
add_subdirectory(demo/socket)