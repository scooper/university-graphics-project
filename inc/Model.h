#ifndef MODEL_H
#define MODEL_H

#include <GL/glut.h>
#include <GL/glu.h>

class Model {

  public:

  Model();
  void loadModel();

  private:

  int _x;
  int _y;
  int _z;
  int _width;
  int _height;
  int _depth;
  GLuint _vboID;



};
#endif
