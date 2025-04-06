#include "ShapeGenerator.hpp"
#include "Vertex.hpp"
#include <cstring>

#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof(*a)

/*
The reason for using dynamically allocated memory is because we want the array to
persist even whent the function ends. When we create an array and get its location,
we actually use a pointer that points at the first index of the array meaning when the
the method ends and we try to access the array WE CANT because it looks for something
that doesnt exist and would probably get a random addresss. The solution?

Use Heap instead of stack!

by using heap we can make an array that doesnt automatically get deleted as the method ends
therefore we can access the array despite all the local variables got destroyed inside the method!
*/

ShapeData ShapeGenerator::makeTriangle() {
    ShapeData ret;
    // A vertex (1) is one point and vertices are the amount of positions within (3)
    Vertex thisTri[] = {

        glm::vec3(-1.0f, +1.0f, +1.0f),  // 0
        glm::vec3(+1.0f, +0.0f, +0.0f),

        glm::vec3(+1.0f, +1.0f, +1.0f),  // 1
        glm::vec3(+0.0f, +1.0f, +0.0f),

        glm::vec3(+1.0f, +1.0f, -1.0f),  // 2
        glm::vec3(+0.0f, +0.0f, +1.0f),

        glm::vec3(-1.0f, +1.0f, -1.0f),  // 3
        glm::vec3(+1.0f, +1.0f, +1.0f),

        glm::vec3(-1.0f, +1.0f, -1.0f),  // 4
        glm::vec3(+1.0f, +0.0f, +1.0f),

        glm::vec3(+1.0f, +1.0f, -1.0f),  // 5
        glm::vec3(+0.0f, +0.5f, +0.2f),

        glm::vec3(+1.0f, -1.0f, -1.0f),  // 6
        glm::vec3(+0.8f, +0.6f, +0.4f),

        glm::vec3(-1.0f, -1.0f, -1.0f),  // 7
        glm::vec3(+0.3f, +1.0f, +0.5f),

        glm::vec3(+1.0f, +1.0f, -1.0f),  // 8
        glm::vec3(+0.2f, +0.5f, +0.2f),

        glm::vec3(+1.0f, +1.0f, +1.0f),  // 9
        glm::vec3(+0.9f, +0.3f, +0.7f),

        glm::vec3(+1.0f, -1.0f, +1.0f),  // 10
        glm::vec3(+0.3f, +0.7f, +1.0f),

        glm::vec3(+1.0f, -1.0f, -1.0f),  // 11
        glm::vec3(+0.5f, +0.7f, +0.5f),

        glm::vec3(-1.0f, +1.0f, +1.0f),  // 12
        glm::vec3(+0.7f, +0.8f, +0.2f),

        glm::vec3(-1.0f, +1.0f, -1.0f),  // 13
        glm::vec3(+0.5f, +0.7f, +0.3f),

        glm::vec3(-1.0f, -1.0f, -1.0f),  // 14
        glm::vec3(+0.4f, +0.7f, +0.7f),

        glm::vec3(-1.0f, -1.0f, +1.0f),  // 15
        glm::vec3(+0.2f, +0.5f, +1.0f),

        glm::vec3(+1.0f, +1.0f, +1.0f),  // 16
        glm::vec3(+0.6f, +1.0f, +0.7f),

        glm::vec3(-1.0f, +1.0f, +1.0f),  // 17
        glm::vec3(+0.6f, +0.4f, +0.8f),

        glm::vec3(-1.0f, -1.0f, +1.0f),  // 18
        glm::vec3(+0.2f, +0.8f, +0.7f),

        glm::vec3(+1.0f, -1.0f, +1.0f),  // 19
        glm::vec3(+0.2f, +0.7f, +1.0f),

        glm::vec3(+1.0f, -1.0f, -1.0f),  // 20
        glm::vec3(+0.8f, +0.3f, +0.7f),

        glm::vec3(-1.0f, -1.0f, -1.0f),  // 21
        glm::vec3(+0.8f, +0.9f, +0.5f),

        glm::vec3(-1.0f, -1.0f, +1.0f),  // 22
        glm::vec3(+0.5f, +0.8f, +0.5f),

        glm::vec3(+1.0f, -1.0f, +1.0f),  // 23
        glm::vec3(+0.9f, +1.0f, +0.2f),

    };

    // This takes the number of elements of ThisTri array
    ret.numVertices = NUM_ARRAY_ELEMENTS(thisTri);
    // Uses the number of elements to determine how big the new allocated array is and since re.vertices is a pointer it stores the first address of the array
    ret.vertices = new Vertex[ret.numVertices];
    // memcpy is a function that transfers data to another array whilst asking how big the array should be
    memcpy(ret.vertices, thisTri, sizeof(thisTri));
    // indices which will be used as a way to render
    GLushort indices[] = {
        0, 1, 2, 0, 2, 3,        // Top
        4, 5, 6, 4, 6, 7,        // Front
        8, 9, 10, 8, 10, 11,     // Right
        12, 13, 14, 12, 14, 15,  // Left
        16, 17, 18, 16, 18, 19,  // Back
        20, 22, 21, 20, 23, 22,  // Bottom

    };
    // This takes the number of indices which is 3
    ret.numIndices = NUM_ARRAY_ELEMENTS(indices);
    // Doing the same process as above
    ret.indices = new GLushort[ret.numIndices];
    memcpy(ret.indices, indices, sizeof(indices));

    return ret;
}
