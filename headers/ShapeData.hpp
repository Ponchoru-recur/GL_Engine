#pragma once
#include <GL/gl.h>

#include "Vertex.hpp"

struct ShapeData {
    ShapeData() : vertices(0), numVertices(0), indices(0), numIndices(0) {}

    Vertex* vertices;

    GLuint numVertices;
    // This will give the pointer location of the array of indices for GL_ELEMENT_ARRAY.
    GLushort* indices;
    // This gets how many elements are inside the indices example 3 because {0,1,2} = 3
    GLuint numIndices;

    GLsizei vertexBufferSize() const {
        return numVertices * sizeof(Vertex);
    }
    GLsizei indexBufferSize() const {
        return numIndices * sizeof(GLushort);
    }

    void cleanup() {
        delete[] vertices;
        delete[] indices;
        numVertices = numIndices = 0;
    }
};
