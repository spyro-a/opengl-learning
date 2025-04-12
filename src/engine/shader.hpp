#pragma once

#include <string>

#include <glad/glad.h>
#include <glm/matrix.hpp>

#include <utils/utils.hpp>

class shader_t {
private:
    unsigned int shader_id;

public:
    shader_t() = default;
    shader_t(const char* vertex_path, const char* fragment_path);

    void bind() const;
    void unbind() const;

    // getters
    inline unsigned int get_id() const { return shader_id; }
    
    // setters
    void set_bool(const std::string& name, bool value) const;
    void set_int(const std::string& name, int value) const;
    void set_float(const std::string& name, float value) const;
    void set_mat4(const std::string& name, const glm::mat4& value) const;
};