#ifndef STRUCTS_H
#define STRUCTS_H

#include <GL/gl.h>

// for vertex positions and normals
struct Vertex3f {
  GLfloat x;
  GLfloat y;
  GLfloat z;
};

// for texture coordinates
struct Vertex2f {
  GLfloat u;
  GLfloat v;
};

// for faces section
struct Index3ui {
  GLuint pi;
  GLuint ti;
  GLuint ni;
};

#endif
