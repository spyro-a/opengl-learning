#pragma once

#include <string>

class texture_t {
private:
    unsigned int texture_id;
    int width, height, channels;

public:
    texture_t() = default;
    texture_t(const std::string& path);

    void bind() const;
    void unbind() const;

    // getters
    inline unsigned int get_id() const { return texture_id; }

    inline int get_width() const { return width; }
    inline int get_height() const { return height; }
    inline int get_channels() const { return channels; }
};