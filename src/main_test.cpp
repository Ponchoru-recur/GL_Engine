// #include <iostream>
// #include <chrono>
// #include <thread>
// #include <glad/glad.h>
// #include <GLFW/glfw3.h>

// const char *vertexShaderSource = "#version 460 core\n"
//     "in layout(location = 0) vec3 Apos;\n"
//     "in layout(location = 1) vec3 vertexColor;\n"
//     ""
//     "out vec3 theColor;\n"
//     "uniform float moveRight;\n"
//     ""
//     "void main(){"
//     "   gl_Position = vec4(Apos, 1.0f);\n"
//     "   gl_Position.x = gl_Position.x + moveRight;"
//     "   theColor = vertexColor;\n"
//     "}\0";

// const char *fragmentShaderSource = "#version 460 core\n"
//     "out vec4 FragColor;\n"
//     ""
//     "in vec3 theColor;\n"
//     ""
//     "void main(){\n"
//     "   FragColor = vec4(theColor, 1.0f);\n"
//     "}\0";

// int main(){
//     int width_window = 580;
//     int height_window = 580;

//     //Explicitly mentioning the version of glfw we're using
//     glfwInit();
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//     GLFWwindow * window = glfwCreateWindow(width_window, height_window, "Banana", NULL, NULL);

//     if (window == NULL){
//         std::cout << "Window Failed to initialized\n";
//         glfwDestroyWindow(window);
//         return -1;
//     }

//     glfwMakeContextCurrent(window);

//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
//         std::cout << "Glad Failed to initialized.\n";
//         glfwTerminate();
//         return -1;
//     }
//     glViewport(0, 0, width_window, height_window);

//     //Compile vertexShader
//     GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//     glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//     glCompileShader(vertexShader);

//     GLint success;
//     char infoLog[512];
//     glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//     if (!success){
//         glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//         std::cout << "VertexShader Failed to compile : " << infoLog << "\n";
//         return -1;
//     }


//     GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//     glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//     glCompileShader(fragmentShader);

//     if (!success){
//         glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//         std::cout << "VertexShader Failed to compile : " << infoLog << "\n";
//         return -1;
//     }

//     GLuint shaderProgram = glCreateProgram();
//     glAttachShader(shaderProgram, vertexShader);
//     glAttachShader(shaderProgram, fragmentShader);
//     glLinkProgram(shaderProgram);

//     glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//     if (!success) {
//         glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//         std::cout << "Shader Program Linking Failed:\n" << infoLog << "\n";
//     }

//     glDeleteShader(vertexShader);
//     glDeleteShader(fragmentShader);

//     //Buffer data
//     //XYZ
//     GLfloat triangle[] = {

//         -0.5f, +0.0f, +0.0f,
//         +1.0f, +0.0f, +1.0f,

//         +0.5f, +0.0f, +0.0f,
//         +1.0f, +0.0f, +1.0f,

//         +0.0f, +0.5f, +0.0f,
//         +1.0f, +0.0f, +1.0f,

//     };

//     GLuint VAO;
//     glGenVertexArrays(1, &VAO);
//     glBindVertexArray(VAO);

//     GLuint vertexBufferID;
//     glGenBuffers(1, &vertexBufferID);
//     glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

//     GLushort indices[] = { 0, 1, 2 };
//     GLuint vertexElementID;
//     glGenBuffers(1, &vertexElementID);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexElementID);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

//     //Describing the position of the array and sending it to the fragmentShaderSource
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (char*)(sizeof(float) * 3));
//     glEnableVertexAttribArray(0);
//     glEnableVertexAttribArray(1);


//     //umbinding it
//     // glBindVertexArray(0);
//     // glBindBuffer(GL_ARRAY_BUFFER, 0);

//     // GLint value;
//     // glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &value);
//     // std::cout << "Value : " << value << std::endl;



//     GLint moveRightUniformLocation = glGetUniformLocation(shaderProgram, "moveRight");
//     GLfloat c = 0.0f;

//     while (!glfwWindowShouldClose(window)){
//         std::this_thread::sleep_for(std::chrono::milliseconds(10));

//         glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);

//         glUseProgram(shaderProgram);
//         glBindVertexArray(VAO);

//         glUniform1f(moveRightUniformLocation, c);
//         c = c + 0.001f;

//         if (c > 1.0f){
//             c = -1.0f;
//         }
//         // glDrawArrays(GL_TRIANGLES, 0, 3);
//         glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);

//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     glfwDestroyWindow(window);
//     glfwTerminate();
//     return 0;
// }
