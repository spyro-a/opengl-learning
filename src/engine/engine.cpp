#include <engine/engine.hpp>

#include <iostream>
#include <utils/utils.hpp>

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
    // macOS specific hint
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    // create window
    window = glfwCreateWindow(800, 600, "OpenGL Window", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "failed to create glfw window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    // initialize glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "failed to initialize glad" << std::endl;
        return;
    }

    // set viewport
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // compile and link shaders
    compile_shader(utils::read_file("shaders/shader.vert"), GL_VERTEX_SHADER);
    compile_shader(utils::read_file("shaders/shader.frag"), GL_FRAGMENT_SHADER);
    compile_shader_program();
}

void engine_t::run() {
    // Define the vertices of the square
    float square_vertices[] = {
        -0.5f, -0.5f, 0.0f,  // left bottom
         0.5f, -0.5f, 0.0f,  // right bottom
         0.5f,  0.5f, 0.0f,  // right top
        -0.5f,  0.5f, 0.0f   // left top
    };

    // Define the indices of the square (two triangles)
    unsigned int square_indices[] = {
        0, 1, 2, // first triangle
        2, 3, 0  // second triangle
    };

    unsigned int VBO, VAO, EBO;

    // generate buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // bind the VAO
    glBindVertexArray(VAO);

    // bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices), square_vertices, GL_STATIC_DRAW);

    // bind the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square_indices), square_indices, GL_STATIC_DRAW);

    // set the vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // unbind the buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // render loop
    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        glClearColor(0.3f, 0.3f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        // use the shader program
        glUseProgram(shader_program);

        // wireframe mode toggle
        if (wireframe_mode)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // bind the VAO and draw the square
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // draw square

        // swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // cleanup: delete the buffers and arrays
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void engine_t::destroy() {
    glDeleteProgram(shader_program);
    glfwDestroyWindow(window);
    glfwTerminate();
}

void engine_t::compile_shader(const std::string& shader_source, unsigned int shader_type) {
    unsigned int shader = glCreateShader(shader_type);

    const char* shader_source_data = shader_source.c_str();
    glShaderSource(shader, 1, &shader_source_data, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info[512];
        glGetShaderInfoLog(shader, 512, nullptr, info);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << info << std::endl;
        return;
    }

    shaders.push_back(shader);
}

void engine_t::compile_shader_program() {
    shader_program = glCreateProgram();

    for (const unsigned int& shader : shaders) {
        glAttachShader(shader_program, shader);
    }

    glLinkProgram(shader_program);

    int success;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        char info[512];
        glGetProgramInfoLog(shader_program, 512, nullptr, info);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info << std::endl;
        return;
    }

    for (unsigned int shader : shaders) {
        glDeleteShader(shader);
    }
}

void engine_t::process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
        system("clear");
    }
}
