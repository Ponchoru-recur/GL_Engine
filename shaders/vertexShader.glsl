#version 460 core\n
in layout (location = 0) vec2 aPos;\n
in layout (location = 1) vec3 vertexColor;\n

out vec3 theColor;\n

void main() {\n
    gl_Position = vec4(aPos, 0.0, 1.0);\n
    theColor = vertexColor;
}\0;
