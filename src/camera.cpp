#include "camera.hpp"

#include <iostream>

Camera::Camera() : viewDirection(0.0f, 0.0f, -1.0f), UP(0.0f, 1.0f, 0.0f) {
}

glm::mat4 Camera::getWorldToViewMatrix() const {
    return glm::lookAt(position, position + viewDirection, UP);
}

void Camera::mouseUpdate(const glm::vec2 &newMousePosition) {
    glm::vec2 mouseDelta = newMousePosition - oldMousePosition;

    float mouse_sense_x = -mouseDelta.x * 0.5;  // 0.5 represents the sensitivity of the rotation of x axis
    float mouse_sense_y = -mouseDelta.y * 0.5;
    if (glm::length(mouse_sense_x) > 60 || glm::length(mouse_sense_y) > 60) {
        oldMousePosition = newMousePosition;
        return;
    }
    // Horizontal
    viewDirection = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(mouse_sense_x), UP)) * viewDirection;
    glm::vec3 toRotateAround = glm::cross(viewDirection, UP);
    viewDirection = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(mouse_sense_y), toRotateAround)) * viewDirection;
    oldMousePosition = newMousePosition;
}
