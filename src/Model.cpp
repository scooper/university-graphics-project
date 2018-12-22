#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <QImage>
#include "Reader.h"
#include "Model.h"
using namespace std;

Model::Model(string obj, string texture) {
  // reads in model of same name
  Reader* r = new Reader(obj);

  if(texture != "") {
    Image image(texture);
    //Generate texture
    glGenTextures(1, &_tbID);
    glBindTexture(GL_TEXTURE_2D, _tbID);
    // gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.Width(), image.Height(), GL_RGB, GL_UNSIGNED_BYTE, image.imageField());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.Width(), image.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.imageField());

    // texture parameters
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D,0);

    //Image image(texpath);
  }

  // retrieve arrays of data
  GLfloat *vertices = r->getVertices();
  GLfloat *texCoords = r->getTextures();
  GLfloat *normals = r->getNormals();
  GLuint *indices = r->getIndicies();

  // calculate buffer content sizes
  vsize = r->getVerticesSize()*sizeof(GLfloat);
  tsize = r->getTexturesSize()*sizeof(GLfloat);
  nsize = r->getNormalsSize()*sizeof(GLfloat);
  numIndices = r->getIndiciesSize();



  //generate a buffer for vbo
  glGenBuffers(1, &_vboID);
  glBindBuffer(GL_ARRAY_BUFFER, _vboID);
  //fill buffer
  glBufferData(GL_ARRAY_BUFFER, vsize+tsize+nsize, 0, GL_STATIC_DRAW);
  //vertices
  glBufferSubData(GL_ARRAY_BUFFER, 0, vsize, &vertices[0]);
  //tex coordinates
  glBufferSubData(GL_ARRAY_BUFFER, vsize, tsize, &texCoords[0]);
  //normals
  glBufferSubData(GL_ARRAY_BUFFER, vsize+tsize, nsize, &normals[0]);
  //colour
  // bind back to nothing
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  //generate buffer for ibo
  glGenBuffers(1, &_iboID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboID);
  //fill buffer with index data
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices*sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
  // bind back to nothing
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  delete r;
}

void Model::draw() {

  // enable lighting and textures
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
  glBindBuffer(GL_ARRAY_BUFFER, _vboID);
  glBindTexture(GL_TEXTURE_2D, _tbID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboID);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, 0);
  glTexCoordPointer(2, GL_FLOAT, 0, (void*)vsize);
  glNormalPointer(GL_FLOAT, 0, (void*)(vsize+tsize));


  // draw buffer contents (using indicies)
  //glDrawArrays(GL_TRIANGLES, 0, 0);
  glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, (void*)0);
  glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  //delete image;
}
#endif
