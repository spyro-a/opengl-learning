#pragma once

#include <string>

#include <GLFW/glfw3.h>


class menu_t {
private:
    std::string title;
    float width, height;

    bool showing = true;

public:
    float radius = 10.0f;
    float cam_x, cam_z;

public:
    menu_t();

    void initialize(GLFWwindow* window);
    void render();
    void destroy();
};