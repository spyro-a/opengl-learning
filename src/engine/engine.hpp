#pragma once

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <engine/shader.hpp>

class engine_t {
private:
    GLFWwindow* window;

    shader_t shader;

    // window resize callback
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }
private:
    bool wireframe_mode = false;

public:
    void initialize();
    void run();
    void destroy();

    void process_input(GLFWwindow* window);

    // setters & getters
    inline void set_wireframe_mode(bool mode) { wireframe_mode = mode; }
};