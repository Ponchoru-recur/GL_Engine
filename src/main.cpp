#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <thread>
#include <vector>

#include "ShapeGenerator.hpp"

int width = 800, height = 600;
int num_indices = 0;

// Vertex Shader Source
const char* vertexShaderSource =
    "#version 460 core\n"
    "in layout (location = 0) vec3 aPos;\n"
    "in layout (location = 1) vec3 vertexColor;\n"
    ""
    "out vec3 theColor;\n"
    "uniform mat4 fullTransformMatrix;\n"
    ""
    ""
    "void main() {\n"
    "   gl_Position = fullTransformMatrix * vec4(aPos, 1.0);\n"
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

float x_offset = 0;
float y_offset = 0;
float x_rotate_offset = 54.0f;

// Input Handling
void ProcessInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        y_offset += 0.1f;
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        y_offset -= 0.1f;
    } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        x_offset += 0.1f;
    } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        x_offset -= 0.1f;
    } else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        x_rotate_offset -= 1.0f;
    } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        x_rotate_offset += 1.0f;
    }
}

int main() {
    // Initialize GLFW
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

    // Create VAO (Important!)
    // This stores how to interpret the vertices else it forgets and probably
    // will show a weird behavior.
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create VBO (Vertex Buffer Object)
    GLuint VertexBufferID;
    glGenBuffers(1, &VertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, tri.vertexBufferSize(), tri.vertices,
                 GL_STATIC_DRAW);

    GLuint indexBufferID;
    glGenBuffers(1, &indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, tri.indexBufferSize(), tri.indices,
                 GL_STATIC_DRAW);
    num_indices = tri.numIndices;
    tri.cleanup();

    // Describe Vertex Data
    // The 0 describes the starting point of the verts. (location of the verts.)
    // The 2 describes the number of components (x,y)
    // What datatype is the component (GL_FLOAT)
    // The GL_FALSE means don't tamper with the fucking spell
    // The 2 * sizeof(float) is i have no fucking idea either
    //(void*)0?????
    // glEnableVertexAttribArray(0); enables OpenGL to send the data to the RAM
    // and the GRAPHICS CARD to send it to the graphics processing pipeline For
    // attribute (zero) expect (two) (GL_FLOAT)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (char*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    // Unbind Buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Main Render Loop
    while (!glfwWindowShouldClose(window)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(30));

        ProcessInput(window);

        // Clears the color and depth
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render Triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        // Cube 1

        // This area calculates how the object will move, rotate and be projected on the screen.
        glm::mat4 projectionMatrix = glm::perspective(glm::radians(60.0f), float(width) / float(height), 0.1f, 10.0f);
        glm::mat4 translationMatrix = glm::translate(projectionMatrix, glm::vec3(x_offset, y_offset, -4.0f));
        glm::mat4 fulltransformMatrix = glm::rotate(translationMatrix, glm::radians(x_rotate_offset), glm::vec3(0.0f, 1.0f, 0.0f));

        // Goes to the shader program and finds fullTransformMatrix
        GLint fullTranslationMatrixLocation = glGetUniformLocation(shaderProgram, "fullTransformMatrix");
        // This function sends the data to the vertexShader
        glUniformMatrix4fv(fullTranslationMatrixLocation, 1, GL_FALSE, &fulltransformMatrix[0][0]);
        // Draw the triangle
        glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_SHORT, 0);

        // Cube 2

        translationMatrix = glm::translate(projectionMatrix, glm::vec3(x_offset - 2.0f, y_offset, -4.0f));
        fulltransformMatrix = glm::rotate(translationMatrix, glm::radians(x_rotate_offset - 20), glm::vec3(0.0f, 1.0f, 0.0f));

        // Goes to the shader program and finds fullTransformMatrix
        fullTranslationMatrixLocation = glGetUniformLocation(shaderProgram, "fullTransformMatrix");
        // This function sends the data to the vertexShader
        glUniformMatrix4fv(fullTranslationMatrixLocation, 1, GL_FALSE, &fulltransformMatrix[0][0]);
        // Draw the triangle
        glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_SHORT, 0);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // **Cleanup**
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VertexBufferID);
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
