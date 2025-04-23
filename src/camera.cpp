#include "camera.hpp"

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
    // Horizontal or left to right
    viewDirection = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(mouse_sense_x), UP)) * viewDirection;
    // vertical or up and down
    glm::vec3 toRotateAround = glm::cross(viewDirection, UP);
    viewDirection = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(mouse_sense_y), toRotateAround)) * viewDirection;
    oldMousePosition = newMousePosition;
}

void Camera::moveForward() {
    position += MOVEMENT_SPEED * viewDirection;
}
void Camera::moveBackward() {
    position += -MOVEMENT_SPEED * viewDirection;
}
void Camera::strafeLeft() {
    glm::vec3 StrafeDirection = glm::cross(viewDirection, UP);
    position += -MOVEMENT_SPEED * StrafeDirection;
}
void Camera::strafeRight() {
    glm::vec3 StrafeDirection = glm::cross(viewDirection, UP);
    position += MOVEMENT_SPEED * StrafeDirection;
}
void Camera::moveUp() {
    position += MOVEMENT_SPEED * UP;
}
void Camera::moveDown() {
    position += -MOVEMENT_SPEED * UP;
}
