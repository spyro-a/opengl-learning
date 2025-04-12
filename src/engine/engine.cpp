#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <engine/engine.hpp>

#include <utils/utils.hpp>

void engine_t::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

engine_t::engine_t() {

}

engine_t::engine_t(int width, int height, const std::string& title) : engine_t() {
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

    glEnable(GL_DEPTH_TEST);

    // make adjustments for retina displays
    int vp_width, vp_height;
    glfwGetFramebufferSize(window.get_window(), &vp_width, &vp_height);
    glViewport(0, 0, vp_width, vp_height);
    glfwSetFramebufferSizeCallback(window.get_window(), framebuffer_size_callback);

    // compile shaders
    shader = shader_t("shaders/shader.vert", "shaders/shader.frag");

    // load textures
    texture = texture_t("res/gradient.png");

    // initialize menu
    menu.initialize(window.get_window());
}

void engine_t::run() {
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // bind the VAO
    glBindVertexArray(VAO);

    // bind and fill the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // set the vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // uv coords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // unbind the objects
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // SRT
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection;

    glm::vec3 camera_position = glm::vec3(0.f, 0.f, 3.0f);
    glm::vec3 camera_target = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 camera_direction = glm::normalize(camera_position - camera_target);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 camera_right = glm::normalize(glm::cross(up, camera_direction));
    glm::vec3 cameraUp = glm::cross(camera_direction, camera_right);

    view = glm::translate(view, glm::vec3(0.f, 0.f, -3.0f));

    // render loop
    while (!glfwWindowShouldClose(window.get_window())) {
        process_input(window.get_window());

        glClearColor(0.3f, 0.3f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (wireframe_mode)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        shader.bind();
        texture.bind();

        model = glm::rotate(model, 0.0f, glm::vec3(1.f, 0.0f, 1.0f));
        projection = glm::perspective(glm::radians(45.f), (float)window.get_width() / (float)window.get_height(), 0.1f, 100.f);

        glm::mat4 view = glm::mat4(1.0f);
        // float radius = 5.0f;
        menu.cam_x = static_cast<float>(sin(glfwGetTime()) * menu.radius);
        menu.cam_z = static_cast<float>(cos(glfwGetTime()) * menu.radius);
        view = glm::lookAt(glm::vec3(menu.cam_x, 0.0f, menu.cam_z), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        
        glBindVertexArray(VAO);
        
        shader.set_mat4("model", model);
        shader.set_mat4("view", view);
        shader.set_mat4("projection", projection);
        
        glDrawArrays(GL_TRIANGLES, 0, 36);

        menu.render();

        glfwSwapBuffers(window.get_window());
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void engine_t::destroy() {
    glDeleteProgram(shader.get_id());
    glfwDestroyWindow(window.get_window());
    glfwTerminate();
}

void engine_t::process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);

    #if defined(__linux__) || defined(__APPLE__)
        system("clear");
    #elif defined(__WIN32__)
        system("cls");
    #endif

    } else if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        wireframe_mode = !wireframe_mode;
    }
}