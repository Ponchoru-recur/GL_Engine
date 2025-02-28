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
  //A vertex (1) is one point and vertices are the amount of positions within (3)
  Vertex thisTri[] = {
      glm::vec3(+0.0f, +1.0f, +0.0f),
      glm::vec3(+1.0f, +0.0f, +0.0f),

      glm::vec3(-1.0f, -1.0f, +0.0f),
      glm::vec3(+0.0f, +1.0f, +0.0f),

      glm::vec3(+1.0f, -1.0f, +0.0f),
      glm::vec3(+0.0f, +0.0f, +1.0f),
  };

  //This takes the number of elements of ThisTri array
  ret.numVertices = NUM_ARRAY_ELEMENTS(thisTri);
  //Uses the number of elements to determine how big the new allocated array is and since re.vertices is a pointer it stores the first address of the array
  ret.vertices = new Vertex[ret.numVertices];
  //memcpy is a function that transfers data to another array whilst asking how big the array should be
  memcpy(ret.vertices, thisTri, sizeof(thisTri));
  //indices which will be used as a way to render
  GLushort indices[] = {0, 1, 2};
  //This takes the number of indices which is 3
  ret.numIndices = NUM_ARRAY_ELEMENTS(indices);
  //Doing the same process as above
  ret.indices = new GLushort[ret.numIndices];
  memcpy(ret.indices, indices, sizeof(indices));

  return ret;
}
