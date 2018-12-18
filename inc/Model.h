#ifndef MODEL_H
#define MODEL_H

#include <GL/glut.h>
#include <GL/glu.h>
#include <string>

using namespace std;

class Model {

  public:

  Model(string filename);
  void draw();
  GLuint _vboID;
  GLuint _iboID;
  size_t vsize;
  size_t nsize;
  size_t csize;
  size_t numIndices;

  private:

  int _x;
  int _y;
  int _z;
  int _width;
  int _height;
  int _depth;



};
#endif
