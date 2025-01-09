#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std; 


int main()
{
    GLFWwindow * window;
    
    if (!glfwInit()) {
        cout << "GLW couldn't start" << endl;
        return -1;
    }

    window = glfwCreateWindow(640, 480, "SV Engine", NULL, NULL);

    glClearColor(2.25f, 0.5f, 0.75f, 1.0f);

    while (!glfwWindowShouldClose(window)){
        glfwPollEvents;

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}