#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Reader.h"
#include "Model.h"

using namespace std;
//
// GLfloat vts[]  = {
//      .5f, .5f, .5f,  -.5f, .5f, .5f,  -.5f,-.5f, .5f,  .5f,-.5f, .5f, // v0,v1,v2,v3 (front)
//      .5f, .5f, .5f,   .5f,-.5f, .5f,   .5f,-.5f,-.5f,  .5f, .5f,-.5f, // v0,v3,v4,v5 (right)
//      .5f, .5f, .5f,   .5f, .5f,-.5f,  -.5f, .5f,-.5f, -.5f, .5f, .5f, // v0,v5,v6,v1 (top)
//     -.5f, .5f, .5f,  -.5f, .5f,-.5f,  -.5f,-.5f,-.5f, -.5f,-.5f, .5f, // v1,v6,v7,v2 (left)
//     -.5f,-.5f,-.5f,   .5f,-.5f,-.5f,   .5f,-.5f, .5f, -.5f,-.5f, .5f, // v7,v4,v3,v2 (bottom)
//      .5f,-.5f,-.5f,  -.5f,-.5f,-.5f,  -.5f, .5f,-.5f,  .5f, .5f,-.5f  // v4,v7,v6,v5 (back)
// };
//
// GLfloat normals[] = {
//    0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,  // v0,v1,v2,v3 (front)
//    1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0,  // v0,v3,v4,v5 (right)
//    0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,  // v0,v5,v6,v1 (top)
//   -1, 0, 0,  -1, 0, 0,  -1, 0, 0,  -1, 0, 0,  // v1,v6,v7,v2 (left)
//    0,-1, 0,   0,-1, 0,   0,-1, 0,   0,-1, 0,  // v7,v4,v3,v2 (bottom)
//    0, 0,-1,   0, 0,-1,   0, 0,-1,   0, 0,-1   // v4,v7,v6,v5 (back)
// };
//
// GLfloat clr[] = {
//   1, 1, 1,   1, 1, 0,   1, 0, 0,   1, 0, 1,  // v0,v1,v2,v3 (front)
//   1, 1, 1,   1, 0, 1,   0, 0, 1,   0, 1, 1,  // v0,v3,v4,v5 (right)
//   1, 1, 1,   0, 1, 1,   0, 1, 0,   1, 1, 0,  // v0,v5,v6,v1 (top)
//   1, 1, 0,   0, 1, 0,   0, 0, 0,   1, 0, 0,  // v1,v6,v7,v2 (left)
//   0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,  // v7,v4,v3,v2 (bottom)
//   0, 0, 1,   0, 0, 0,   0, 1, 0,   0, 1, 1   // v4,v7,v6,v5 (back)
// };
//
// GLuint indices[] = {
//   0, 1, 2,   2, 3, 0,    // v0-v1-v2, v2-v3-v0 (front)
//   4, 5, 6,   6, 7, 4,    // v0-v3-v4, v4-v5-v0 (right)
//   8, 9,10,  10,11, 8,    // v0-v5-v6, v6-v1-v0 (top)
//   12,13,14,  14,15,12,    // v1-v6-v7, v7-v2-v1 (left)
//   16,17,18,  18,19,16,    // v7-v4-v3, v3-v2-v7 (bottom)
//   20,21,22,  22,23,20     // v4-v7-v6, v6-v5-v4 (back)
// };

Model::Model(string filename) {

  // create new reader, with argument of filename above
  // assign integers below based on getters
  // fill buffers based on vectors
  // delete reader afterwards

  Reader* r = new Reader(filename);

  vector<GLfloat> vertices = r->getVertices();
  vector<GLfloat> normals = r->getNormals();
  vector<GLfloat> colour = r->getColour();
  vector<GLuint> indices = r->getIndicies();

  vsize = vertices.size()*sizeof(GLfloat);
  nsize = normals.size()*sizeof(GLfloat);
  csize = colour.size()*sizeof(GLfloat);
  numIndices = indices.size();

  glGenBuffers(1, &_vboID);
  glBindBuffer(GL_ARRAY_BUFFER, _vboID);
  //fill buffer
  glBufferData(GL_ARRAY_BUFFER, vsize+nsize+csize, 0, GL_STATIC_DRAW);
  //vertices
  glBufferSubData(GL_ARRAY_BUFFER, 0, vsize, vertices.data());
  //normals
  glBufferSubData(GL_ARRAY_BUFFER, vsize, nsize, normals.data());
  //colour
  glBufferSubData(GL_ARRAY_BUFFER, vsize+nsize, csize, colour.data());

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  //indices
  glGenBuffers(1, &_iboID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices*sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  //free memory
  delete r;
  // delete vts;
  // delete normals;
  // delete clr;
  // delete indices;
  // vbos
  // glGenBuffers
  // glBindBuffer GL_ARRAY_BUFFER
  // glVertexPointer
  // glColourPointer
  // glTexCoordPointer

}

void Model::draw() {
  glBindBuffer(GL_ARRAY_BUFFER, _vboID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboID);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, 0);
  glNormalPointer(GL_FLOAT, 0, (void*)vsize);
  glColorPointer(3, GL_FLOAT, 0, (void*)(vsize+nsize));
  // draw buffer contents (change the 36 to whatever stored indicies size)
  glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, (void*)0);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
#endif
