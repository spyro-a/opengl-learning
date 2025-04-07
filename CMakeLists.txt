cmake_minimum_required(VERSION 3.31..)
project(opengl-dev LANGUAGES C CXX)

SET(CMAKE_CXX_STANDARD 14)

FILE(GLOB SOURCES
    src/engine/*.cpp
    src/*.cpp
)

add_subdirectory(vendor)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL
    glfw
    glad
)