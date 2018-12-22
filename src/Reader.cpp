/*************************************
 *  Parser for obj files, returns    *
 *  arrays of vertex and index data  *
 *************************************/
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <GL/gl.h>
#include "Reader.h"
#include "Structs.h"
//#include <GL/glut.h>

using namespace std;
// figure out indexing (start by fixing normals), using vertex indicies atm
// figure out textures

Reader::Reader(string filename) {
  string line;
  string type;
  ifstream inputFile(filename, ios::in);
  if(inputFile.is_open()) {
    // while input is available
    while(getline(inputFile, line)) {
      // its a comment or empty space, skip
      if(line == "" || line[0] == '#')
        continue;
      // get first string available
      istringstream stream(line);
      stream >> type;
      if(type == "v") {
        Vertex3f vertex; // to hold primitive values
        // use sscanf to skip to assigning float values
        sscanf(line.c_str(), "%*s %f %f %f", &vertex.x, &vertex.y, &vertex.z);
        vertices.push_back(vertex);
        //colour.push_back((GLfloat)1.0);
      }
      if(type == "vt") {
        Vertex2f texture; // to hold u,v texture coordinates
        // use sscanf to skip to assigning float values
        sscanf(line.c_str(), "%*s %f %f", &texture.u, &texture.v);
        textures.push_back(texture);
      }
      if(type == "vn") {
        Vertex3f normal; // to hold vertex normals
        // use sscanf to skip to assigning float values
        sscanf(line.c_str(), "%*s %f %f %f", &normal.x, &normal.y, &normal.z);
        normals.push_back(normal);
      }
      // break from loop when s is reached (s is always before f in my version of blender obj)
      if (type == "s") {
        normSize = vertices.size()*3;
        normalArray = new GLfloat[normSize];// array to hold normals
        txtrSize = vertices.size()*2;
        textureArray = new GLfloat[txtrSize];
        break;
      }
    }
    // start reordering vertex attributes and condensing indices into one list
    while(getline(inputFile, line)) {
      // each vertex in triangle attribute indices
      Index3ui index1;
      Index3ui index2;
      Index3ui index3;

      // put the file input into the arrays
      sscanf(line.c_str(), "%*s %d/%d/%d %d/%d/%d %d/%d/%d", &index1.pi,
      &index1.ti,&index1.ni,&index2.pi,&index2.ti,&index2.ni,&index3.pi,
      &index3.ti,&index3.ni);

      // process indices
      this->indexing(index1);
      this->indexing(index2);
      this->indexing(index3);

    }
    // create arrays to fill and eventually use in VBO
    vertSize = vertices.size()*3;
    vertexArray = new GLfloat[vertSize];
    indiSize = indices.size();
    indicesArray = new GLuint[indiSize];

    // fill vertex array with vertex vector contents
    // basically just transfer contents to array
    int indexNum = 0;
    for (size_t i = 0; i < vertices.size(); i++) {
      Vertex3f vertex = vertices.at(i);
      vertexArray[indexNum++] = vertex.x;
      vertexArray[indexNum++] = vertex.y;
      vertexArray[indexNum++] = vertex.z;
    }
    // same with indices
    for (size_t i = 0; i < indices.size(); i++) {
      indicesArray[i] = indices.at(i);
    }

  } else {
    cerr << "cannot open file \"" << filename << "\"" << "\n";
  }

}

// reorders normal and texture indices to fit same order and amount as vertex indices
void Reader::indexing(Index3ui index) {
 int vertexP = index.pi-1;
 indices.push_back(vertexP);
 Vertex2f cTexture = textures.at(index.ti-1);
 textureArray[vertexP*2] = cTexture.u;
 textureArray[vertexP*2+1] = cTexture.v;
 Vertex3f cNormal = normals.at(index.ni-1);
 normalArray[vertexP*3] = cNormal.x;
 normalArray[vertexP*3+1] = cNormal.y;
 normalArray[vertexP*3+2] = cNormal.z;
}

GLfloat* Reader::getVertices() {
  return vertexArray;
}

GLfloat* Reader::getTextures() {
  return textureArray;
}

GLfloat* Reader::getNormals() {
  return normalArray;
}

GLuint* Reader::getIndicies() {
  return indicesArray;
}

int Reader::getVerticesSize() {
  return vertSize;
}

int Reader::getTexturesSize() {
  return txtrSize;
}

int Reader::getNormalsSize() {
  return normSize;
}

int Reader::getIndiciesSize() {
  return indiSize;
}

// destructor
Reader::~Reader() {
  delete vertexArray;
  delete textureArray;
  delete normalArray;
  delete indicesArray;
}
