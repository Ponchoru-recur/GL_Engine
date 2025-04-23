#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <thread>
#include <vector>

#include "ShapeGenerator.hpp"
#include "camera.hpp"

int width = 1000, height = 700;
int num_indices = 0;

// Vertex Shader Source
const char* vertexShaderSource =
    "#version 460 core\n"
    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec3 vertexColor;\n"
    "layout (location = 2) in mat4 fullTransformMatrix;\n"
    ""
    "uniform vec3 offsets;\n"
    "out vec3 theColor;\n"
    ""
    "void main() {\n"
    "   gl_Position = fullTransformMatrix * vec4(position.x + offsets.x, position.y + offsets.y, position.z + offsets.z, 1.0);\n"
    ""
    "   theColor = vertexColor;\n"
    "}\0";

// Fragment Shader Source
// Runs many more times compared to vertexShader
const char* fragmentShaderSource =
    "#version 460 core\n"
    "out vec4 FragColor;\n"
    ""
    "in vec3 theColor;\n"
    ""
    "void main() {\n"
    "    FragColor = vec4(theColor, 0.5f);\n"
    "}\0";

float x_offset = +1.0f;
float y_offset = 0;
float z_offset = 0.0f;

// Input Handling
void ProcessInput(GLFWwindow* window) {
}

double mouse_x, mouse_y;

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    glm::vec2 newMousePos(xpos, ypos);
    mouse_x = newMousePos.x;
    mouse_y = newMousePos.y;
}

int main() {
    // Initialize GLFW5
    glfwInit();
    // GLFW doesn't know what version we're using thus we write the
    // specification needed, and for this I am using 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    // This clarifies which OpengGL we'll be using (I will be using
    // GLFW_OPENGLE_CORE_PROFILE because the other is too hard to learn which is
    // called Immediate mode)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // This is the window where everything else will be placed
    GLFWwindow* window =
        glfwCreateWindow(width, height, "Triangle", NULL, NULL);
    // Checking whether the making of window was successful
    if (!window) {
        std::cout << "WINDOW Failed to Initialize\n";
        glfwTerminate();
        return -1;
    }
    // Use the window as the current window because you need to be specific on
    // which window you're using (which is weird)
    glfwMakeContextCurrent(window);
    // caps the frames to 144 (because my laptop runs on 144hz)
    //  glfwSwapInterval(1);

    // Checks and loads GLAD which is a library that basically finds the
    // pointers for OpenGL since it is OS specific meaning each operating system
    // has different pointer location etc

    glfwSetCursorPosCallback(window, mouse_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD Failed to Initialize\n";
        glfwTerminate();
        return -1;
    }
    // This sets WHERE the area is allowed to get rendered
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    // FIXME:
    ShapeData tri = ShapeGenerator::makeTriangle();
    Camera camera;

    // Compile Vertex Shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Basically says get shader info and check if there's a problem
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Vertex Shader Compilation Failed:\n"
                  << infoLog << "\n";
    }

    // Compile Fragment Shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check for errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Fragment Shader Compilation Failed:\n"
                  << infoLog << "\n";
    }

    // Link Shaders into a Program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Shader Program Linking Failed:\n"
                  << infoLog << "\n";
    }

    // Delete Shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    num_indices = tri.numIndices;

    // Create VAO (Important!)
    // This stores how to interpret the vertices else it forgets and probably
    // will show a weird behavior.
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create VBO (Vertex Buffer Object) this for the position of triangles
    GLuint VertexBufferID;
    glGenBuffers(1, &VertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, tri.vertexBufferSize(), tri.vertices,
                 GL_STATIC_DRAW);

    // Position vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    // Color vertex
    // glVertexAttrib3f(1, 0, 1, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    GLuint indexBufferID;
    glGenBuffers(1, &indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, tri.indexBufferSize(), tri.indices,
                 GL_STATIC_DRAW);

    GLuint fullTransformationMatrixBufferID;
    glGenBuffers(1, &fullTransformationMatrixBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, fullTransformationMatrixBufferID);

    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * 2, 0, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 0));
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 4));
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 8));
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 12));
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);

    tri.cleanup();

    // Unbind Buffers
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Main Render Loop
    while (!glfwWindowShouldClose(window)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));

        // This is the keypress events
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            camera.moveUp();
        } else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            camera.moveDown();
        } else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            camera.moveForward();
        } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            camera.moveBackward();
        } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            camera.strafeLeft();
        } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            camera.strafeRight();
        }

        // std::cout << "x : " << mouse_x << " y: " << mouse_y << "\n";

        // Clears the color and depth
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // GLuint offsetLocation = glGetUniformLocation(shaderProgram, "offsets");
        // glUniform3f(offsetLocation, x_offset, y_offset, z_offset);

        // Render Triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        camera.mouseUpdate(glm::vec2(mouse_x, mouse_y));
        glm::mat4 projectionMatrix = glm::perspective(glm::radians(60.0f), float(width) / float(height), 0.1f, 10.0f);
        glm::mat4 fullTransforms[] = {
            // Cube 1 (Model to world matrix)
            projectionMatrix * camera.getWorldToViewMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3(x_offset - 2.0f, y_offset, z_offset - 3.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(36.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
            projectionMatrix * camera.getWorldToViewMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3(x_offset, y_offset, z_offset - 3.76f)) * glm::rotate(glm::mat4(1.0f), glm::radians(126.0f), glm::vec3(0.0f, 1.0f, 0.0f))};

        glBufferData(GL_ARRAY_BUFFER, sizeof(fullTransforms), fullTransforms, GL_DYNAMIC_DRAW);

        glDrawElementsInstanced(GL_TRIANGLES, num_indices, GL_UNSIGNED_SHORT, 0, 2);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // **Cleanup**
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VertexBufferID);
    glDeleteBuffers(1, &indexBufferID);
    glDeleteBuffers(1, &fullTransformationMatrixBufferID);
    // glDeleteBuffers(1, &fullTransformationMatrixBufferID);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

/*
    MODELTRANSFORM
    [MT] * V -> np (or new position vector)
    Take the new position vector or np and use it to the projection matrix
    [P] * np
    which will have a new position which is the projected space (A flat thing)

*/

// Describe Vertex Data
// The 0 describes which location will it go to
// The 2 describes the number of components (x,y)
// What datatype is the component (GL_FLOAT)
// The GL_FALSE means don't tamper with the fucking spell
// The 2 * sizeof(float) is i have no fucking idea either
//(void*)0?????
// glEnableVertexAttribArray(0); enables OpenGL to send the data to the RAM
// and the GRAPHICS CARD to send it to the graphics processing pipeline For
// attribute (zero) expect (two) (GL_FLOAT)
