// #include <iostream>
// #include <glad/glad.h>
// #include <GLFW/glfw3.h>




// int main(){


//     int w_width = 580, w_height = 580;

//     glfwInit();
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//     GLFWwindow * window = glfwCreateWindow(w_width, w_height, "My future behold", NULL, NULL);
//     if (window == NULL){
//         std::cerr << "Error on window";
//         return -1;
//     }
//     glfwMakeContextCurrent(window);

//     if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress))){
//         std::cerr << "A problem has occured in glad\n";
//         glfwTerminate();
//         return -1;
//     }

//     glViewport(0,0, w_width, w_height);


//     while (!glfwWindowShouldClose(window))
//     {

//         glClearColor(1.0f,0.0f,0.0f,0.0f);
//         glClear(GL_COLOR_BUFFER_BIT);
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }
//     glfwDestroyWindow(window);
//     glfwTerminate();
//     return 0;
// }
