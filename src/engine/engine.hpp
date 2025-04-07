#pragma once

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class engine_t {
private:
    GLFWwindow* window;

    std::vector<unsigned int> shaders;
    unsigned int shader_program;

    // window resize callback
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }
private:
    bool wireframe_mode = false;

public:
    engine_t() = default;

    void initialize();
    void run();
    void destroy();

    void compile_shader(const std::string& shader_source, unsigned int shader_type);
    void compile_shader_program();

    void process_input(GLFWwindow* window);

    // setters & getters
    inline void set_wireframe_mode(bool mode) { wireframe_mode = mode; }
};