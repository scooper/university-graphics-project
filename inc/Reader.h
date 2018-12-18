#ifndef READER_H
#define READER_H
#include <string>
#include <vector>
#include <GL/gl.h>

// #include <GL/glu.h>
// #include <GL/glut.h>
using namespace std;

class Reader {
  public:
  Reader(string filename);
  vector<GLfloat> getVertices();
  vector<GLfloat> getNormals();
  vector<GLfloat> getColour();
  vector<GLuint> getIndicies();


  private:
  vector<GLfloat> vertices;
  vector<GLfloat> normals;
  vector<GLfloat> colour;
  vector<GLuint> indices;
  //GLfloat vertices;
  //GLfloat normals;
  //GLuint indices;

};

#endif
