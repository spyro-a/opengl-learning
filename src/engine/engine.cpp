#include <iostream>

#include <engine/engine.hpp>

#include <utils/utils.hpp>

void engine_t::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

engine_t::engine_t(int width, int height, const std::string& title) {
    window.set_width(width);
    window.set_height(height);
    window.set_title(title);
}

void engine_t::initialize() {
    // initialize glfw
    if (!glfwInit()) {
        std::cerr << "failed to initialize GLFW" << std::endl;
        return;
    }

    // set OpenGL version (3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // set profile to core
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    // create window
    window.set_window(glfwCreateWindow(window.get_width(), window.get_height(), window.get_title().c_str(), nullptr, nullptr));
    if (window.get_window() == nullptr) {
        std::cerr << "failed to create glfw window" << std::endl;
        glfwTerminate();
        return;
    }
    
    glfwMakeContextCurrent(window.get_window());

    // initialize glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "failed to initialize glad" << std::endl;
        return;
    }

    // make adjustments for retina displays
    int vp_width, vp_height;
    glfwGetFramebufferSize(window.get_window(), &vp_width, &vp_height);
    glViewport(0, 0, vp_width, vp_height);
    glfwSetFramebufferSizeCallback(window.get_window(), framebuffer_size_callback);

    // compile shaders
    shader = shader_t("shaders/shader.vert", "shaders/shader.frag");
    texture = texture_t("res/house.png");
}

void engine_t::run() {
    float vertices[] = {
        // positions          // colors
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, // top left
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // bind the VAO
    glBindVertexArray(VAO);

    // bind and fill the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // bind and fill the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // params: index/location, size, type, normalized (only for integer params), stride (1 vertex), ptr offset (?)

    // set the vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture coordinates
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // unbind the VBO (the EBO is stored in the VAO state)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // render loop
    while (!glfwWindowShouldClose(window.get_window())) {
        process_input(window.get_window());

        glClearColor(0.3f, 0.3f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.bind();

        if (wireframe_mode)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // bind the VAO and draw the triangles to form a rectangle
        glBindVertexArray(VAO);
        glBindTexture(GL_TEXTURE_2D, texture.get_texture_id());
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window.get_window());
        glfwPollEvents();
    }

    // cleanup: delete the buffers and arrays
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void engine_t::destroy() {
    glDeleteProgram(shader.shader_id);
    glfwDestroyWindow(window.get_window());
    glfwTerminate();
}

void engine_t::process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
        system("clear");
    }
}