#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <GL/gl.h>
#include "Reader.h"
//#include <GL/glut.h>

using namespace std;
// figure out indexing (start by fixing normals), using vertex indicies atm
// figure out textures

Reader::Reader(string filename) {
  string line;
  string type;
  ifstream inputFile(filename, ios::in);
  if(inputFile.is_open()) {
    vector<GLfloat> tempv;
    vector<GLfloat> tempn;
    //vector<GLfloat> tempt;
    vector<GLuint> viList;
    vector<GLuint> niList;
    //vector<Gluint> ti;

    // while input is available
    GLuint i = 1;
    while(getline(inputFile, line)) {
      // its a comment or empty space, skip
      if(line == "" || line[0] == '#')
        continue;
      // get first string available
      istringstream stream(line);
      stream >> type;
      if(type == "v") {
        GLfloat vertex[3]; // to hold primitive values
        // use sscanf to skip to assigning float values
        sscanf(line.c_str(), "%*s %f %f %f", &vertex[0], &vertex[1], &vertex[2]);
        tempv.push_back(vertex[0]);
        tempv.push_back(vertex[1]);
        tempv.push_back(vertex[2]);
        //colour.push_back((GLfloat)1.0);
      }
      if(type == "vn") {
        GLfloat normal[3]; // to hold primitive values
        // use sscanf to skip to assigning float values
        sscanf(line.c_str(), "%*s %f %f %f", &normal[0], &normal[1], &normal[2]);
        tempn.push_back(normal[0]);
        tempn.push_back(normal[1]);
        tempn.push_back(normal[2]);
      }
      // this is totally not optimal
      if (type == "f") {
        GLuint index[9];
        sscanf(line.c_str(), "%*s %d//%d %d//%d %d//%d", &index[0],
        &index[1],&index[2],&index[3],&index[4],&index[5]/*,&index[6],
        &index[7],&index[8])*/);
        cout << index[0] << "\n";
        cout << index[2] << "\n";
        viList.push_back(index[0]);
        niList.push_back(index[1]);
        viList.push_back(index[2]);
        niList.push_back(index[3]);
        viList.push_back(index[4]);
        niList.push_back(index[5]);
      }
    }
    // sort indexing
    GLuint index = 0;
    for (size_t i = 0; i < tempv.size(); i++) {
      GLuint vi = viList.at(i);
      GLuint ni = niList.at(i);

      GLfloat v = tempv.at(vi);
      GLfloat n = tempn.at(ni);

      //check if in vector already
      vector<GLfloat>::iterator vit = find(vertices.begin(), vertices.end(), v);
      GLuint hv = distance(vertices.begin(), vit);
      vector<GLfloat>::iterator nit = find(normals.begin(), normals.end(), n);
      GLuint nv = distance(normals.begin(), nit);
      cout << hv << " " << nv << "\n";
      GLfloat t = tempv.at(i);
      if (nv != -1 && hv == nv) {
        indices.push_back(hv);
      } else {
        vertices.push_back(v);
        normals.push_back(n);
        indices.push_back(vertices.size()-1);
      }
    }
  } else {
    cerr << "cannot open file \"" << filename << "\"" << "\n";
  }

}

vector<GLfloat> Reader::getVertices() {
  return vertices;
}

vector<GLfloat> Reader::getNormals() {
  return normals;
}

vector<GLfloat> Reader::getColour() {
  return colour;
}

vector<GLuint> Reader::getIndicies() {
  return indices;
}

// int main(int argc, char const *argv[]) {
//   Reader* read = new Reader("../cwk2/models/monko.obj");
//   vector<unsigned int> ind = read->getIndicies();
//   for (size_t i = 0; i < ind.size(); i++) {
//     cout << ind.at(i) << "\n";
//   }
//   delete read;
//   return 0;
// }
