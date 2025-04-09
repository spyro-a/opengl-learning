#pragma once

#include <string>

#include <GLFW/glfw3.h>

class window_t {
private:
    GLFWwindow* window;

    int width;
    int height;

    std::string title;
    
public:
    window_t() : window(nullptr), width(800), height(600), title("OpenGL Window") {}

    // setters
    inline void set_width(int w) { width = w; }
    inline void set_height(int h) { height = h; }
    inline void set_title(const std::string& t) { title = t; }
    inline void set_window(GLFWwindow* w) { window = w; }

    // getters
    inline int get_width() const { return width; }
    inline int get_height() const { return height; }
    inline const std::string& get_title() const { return title; }
    inline GLFWwindow* get_window() const { return window; }
};