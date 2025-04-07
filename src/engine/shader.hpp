#pragma once

#include <string>

#include <glad/glad.h>

#include <utils/utils.hpp>

class shader_t {
public:
    unsigned int shader_id;

    shader_t() = default;
    shader_t(const char* vertex_path, const char* fragment_path);

    void use();
    void set_bool(const std::string& name, bool value) const;
    void set_int(const std::string& name, int value) const;
    void set_float(const std::string& name, float value) const;
};