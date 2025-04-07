#include <engine/shader.hpp>

shader_t::shader_t(const char* vertex_path, const char* fragment_path) {
    std::string vertex_code = utils::read_file(vertex_path);
    std::string fragment_code = utils::read_file(fragment_path);

    unsigned int vertex, fragment;
    int success;
    char info[512];

    // compile vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    const char* vertex_shader_code = vertex_code.c_str();
    glShaderSource(vertex, 1, &vertex_shader_code, nullptr);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, info);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info << std::endl;
    }

    // compile fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragment_shader_code = fragment_code.c_str();
    glShaderSource(fragment, 1, &fragment_shader_code, nullptr);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, nullptr, info);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info << std::endl;
    }

    // link shaders
    shader_id = glCreateProgram();
    glAttachShader(shader_id, vertex);
    glAttachShader(shader_id, fragment);
    glLinkProgram(shader_id);

    glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_id, 512, nullptr, info);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    
}

void shader_t::use() {
    glUseProgram(shader_id);
}

void shader_t::set_bool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(shader_id, name.c_str()), (int)value);
}

void shader_t::set_int(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(shader_id, name.c_str()), value);
}

void shader_t::set_float(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(shader_id, name.c_str()), value);
}