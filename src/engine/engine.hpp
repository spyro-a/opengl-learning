#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <engine/camera.hpp>
#include <engine/shader.hpp>
#include <engine/texture.hpp>

#include <menu/menu.hpp>

#include <window/window.hpp>

class engine_t {
private:
    window_t window;
    menu_t menu;

    camera_t camera;

    shader_t shader;
    texture_t texture;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

private:
    bool wireframe_mode = false;

    float delta_time = 0.0f;
    float last_frame_time = 0.0f;

public:
    engine_t();
    engine_t(int width, int height, const std::string& title);

    void initialize();
    void run();
    void destroy();

    void process_input(GLFWwindow* window);

    inline window_t* get_window() { return &window; }
    inline camera_t* get_camera() { return &camera; }
};