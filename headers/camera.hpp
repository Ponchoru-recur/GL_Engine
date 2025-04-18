#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
   public:
    Camera();
    void mouseUpdate(const glm::vec2 &newMousePosition);
    glm::mat4 getWorldToViewMatrix() const;

   private:
    glm::vec3 position;       // Positions where the camera stays in the grid
    glm::vec3 viewDirection;  // Where the camera is looking at
    const glm::vec3 UP;
    glm::vec2 oldMousePosition;
};

/*
Insights :
    so the way a camera works in Opengl has two characteristics and
    that is where it is and where to look at.

    so in a nutshell you need two coordinates,
    One is for the position of the camera.
    Second is where to look at and it is also a coordinate.
*/
