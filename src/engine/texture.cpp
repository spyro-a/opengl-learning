#include <engine/texture.hpp>

#include <iostream>

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

texture_t::texture_t(const std::string& path) {
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nr_channels, 0);

    if (data) {
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);

        // set texture wrapping and filtering options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        GLenum pixel_format;
        if (nr_channels == 1) {
            pixel_format = GL_RED;
        } else if (nr_channels == 3) {
            pixel_format = GL_RGB;
        } else if (nr_channels == 4) {
            pixel_format = GL_RGBA;
        } else {
            std::cerr << "unsupported number of channels: " << nr_channels << std::endl;
            stbi_image_free(data);
            return;
        }

        // load texture data
        glTexImage2D(GL_TEXTURE_2D, 0, pixel_format, width, height, 0, pixel_format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    } else {
        std::cerr << "failed to load texture: " << path << std::endl;
    }
}