#ifndef MODEL_H
#define MODEL_H

#include <GL/glut.h>
#include <GL/glu.h>
#include <string>
#include <QImage>
#include "Image.h"

using namespace std;

class Model {

  public:

  Model(string obj, string texture);
  void draw();
  //Image _image;

  private:
  GLuint _vboID;
  GLuint _iboID;
  GLuint _tbID;
  size_t vsize;
  size_t tsize;
  size_t nsize;
  size_t csize;
  size_t numIndices;

};
#endif
