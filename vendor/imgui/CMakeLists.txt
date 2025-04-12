cmake_minimum_required(VERSION 3.31..)
project(imgui LANGUAGES CXX)

add_library(imgui STATIC
    imgui_impl_glfw.cpp
    imgui_impl_opengl3.cpp

    imgui_stdlib.cpp

    imgui_demo.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui.cpp
)

# find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    # OpenGL::GL
    glfw
)