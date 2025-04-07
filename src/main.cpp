#include <cstdlib>

#include <engine/engine.hpp>

#define GL_SILENCE_DEPRECATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// process input
// void process_input(GLFWwindow* window) {
//     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, true);
// }

float triangle_vertices[] = {
    -0.5f, -0.5f, 0.0f,  // left 
     0.5f, -0.5f, 0.0f,  // right
     0.0f,  0.5f, 0.0f   // top
};

int main() {
    engine_t engine;
    engine.initialize();
    engine.set_wireframe_mode(true);
    engine.run();
    
    /*
    GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
    GL_STATIC_DRAW: the data is set only once and used many times.
    GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
    */

    engine.destroy();

    return EXIT_SUCCESS;
}