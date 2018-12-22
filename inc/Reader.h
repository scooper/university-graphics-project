#ifndef READER_H
#define READER_H
#include <string>
#include <vector>
#include <GL/gl.h>
#include "Structs.h"

// #include <GL/glu.h>
// #include <GL/glut.h>
using namespace std;

class Reader {
  public:
  Reader(string filename);
  ~Reader();
  GLfloat* getVertices();
  GLfloat* getTextures();
  GLfloat* getNormals();
  GLfloat* getColour();
  GLuint* getIndicies();
  int getVerticesSize();
  int getTexturesSize();
  int getNormalsSize();
  int getIndiciesSize();


  private:
  vector<Vertex3f> vertices;
  vector<Vertex3f> normals;
  vector<Vertex2f> textures;
  vector<Vertex3f> colour;
  vector<GLuint> indices;
  void indexing(Index3ui index);
  GLfloat *vertexArray;
  GLfloat *normalArray;
  GLfloat *textureArray;
  GLuint *indicesArray;
  int vertSize;
  int normSize;
  int txtrSize;
  int indiSize;
  //GLfloat vertices;
  //GLfloat normals;
  //GLuint indices;

};

#endif
