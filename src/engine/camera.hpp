#pragma once

#include <glm/glm.hpp>

constexpr glm::vec3 CAMERA_FRONT = glm::vec3(0.0f, 0.0f, -1.0f);
constexpr glm::vec3 CAMERA_UP = glm::vec3(0.0f, 1.0f, 0.0f);

class camera_t {
public:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);

    float yaw = -90.0f;
    float pitch = 0.0f;

    float field_of_view = 45.0f;
    float speed = 5.0f;

    camera_t() = default;
};