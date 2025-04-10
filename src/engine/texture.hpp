#pragma once

#include <string>

class texture_t {
private:
    unsigned int texture_id;
    int width, height, nr_channels;

public:
    texture_t() = default;
    texture_t(const std::string& path);

    inline unsigned int get_texture_id() const { return texture_id; }
};