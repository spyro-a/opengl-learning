cmake_minimum_required(VERSION 3.31..)
project(glad LANGUAGES C CXX)

add_library(glad STATIC
    src/glad.c
)

target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    include
)