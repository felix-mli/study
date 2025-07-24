cmake_minimum_required(VERSION 3.10)
project(learn_gtest)

set(CMAKE_C_STANDARD 99)

add_subdirectory(tools/base)
add_subdirectory(tools/cli)

# gtest demo
add_subdirectory(3rdparty/googletest-1.17.0)
add_subdirectory(demo/gtest)

# cjson demo
add_subdirectory(3rdparty/cJSON-1.7.18)
add_subdirectory(demo/cjson)

# socket demo
add_subdirectory(demo/socket)

# mbedtls demo
add_subdirectory(3rdparty/mbedtls-mbedtls-3.6.3)
add_subdirectory(demo/mbedtls)