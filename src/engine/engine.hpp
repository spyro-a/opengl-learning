#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <engine/shader.hpp>

#include <window/window.hpp>

class engine_t {
private:
    window_t window;

    shader_t shader;

    // window resize callback
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

private:
    bool wireframe_mode = false;

public:
    engine_t() = default;
    engine_t(int width, int height, const std::string& title);

    void initialize();
    void run();
    void destroy();

    void process_input(GLFWwindow* window);

    // setters & getters
    inline void set_wireframe_mode(bool mode) { wireframe_mode = mode; }
};