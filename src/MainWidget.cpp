#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES
#include <GL/glu.h>
#include <GL/glut.h>
#include <QGLWidget>
#include <QKeyEvent>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cmath>
#include "MainWidget.h"
#include "Image.h"



// Setting up material properties
typedef struct materialStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;


static materialStruct brassMaterials = {
  { 0.33, 0.22, 0.03, 1.0},
  { 0.78, 0.57, 0.11, 1.0},
  { 0.99, 0.91, 0.81, 1.0},
  27.8
};

// constructor
MainWidget::MainWidget(QWidget *parent)
	: QGLWidget(parent)
	{ // constructor
    setFocusPolicy(Qt::ClickFocus);
	} // constructor

void MainWidget::randomizeBushes() {
  srand(time(NULL));
  for (size_t i = 0; i < NUM_BUSHES; i++) {
    randomBushPos[0][i] = (float)(rand() % NUM_BUSHES + 1);
    randomBushPos[1][i] = (float)(rand() % NUM_BUSHES + 1);
  }
}

void MainWidget::setFogDensity(int value) {
  fogDens = (float)value/1000;
}

void MainWidget::setWorldAngle(int value) {
  worldAngle = value;
}

// called when OpenGL context is set up
void MainWidget::initializeGL()
	{ // initializeGL()

    // set the widget background colour
    glClearColor(0.4, 0.4, 0.9, 0.0);
    // create all VBOs from OBJs
    character = new Character();
    model = new Model("models/suzanneT.obj", "");
    box = new Model("models/subbox.obj", "textures/box.ppm");
    floor = new Model("models/floor.obj", "textures/grass.png");
    path = new Model("models/path.obj", "textures/path.ppm");
    treeLeaves = new Model("models/treeleaves.obj", "textures/treeleaves.ppm");
    building = new Model("models/building.obj", "textures/building.ppm");

    // assign random positions for bushes
    this->randomizeBushes();

    // sphere texture setup
    {
      Image image("textures/earth.ppm");
      glGenTextures(1, &sptexId);
      glBindTexture(GL_TEXTURE_2D, sptexId);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.Width(), image.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.imageField());
      // texture parameters
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glBindTexture(GL_TEXTURE_2D, 0);
    }


    GLfloat fogColor[4]= {0.5f, 0.5f, 0.5f, 1.0f};
    glFogi(GL_FOG_MODE, GL_EXP2);
    glFogfv(GL_FOG_COLOR, fogColor);
    // glHint(GL_FOG_HINT, GL_DONT_CARE);
    glFogf(GL_FOG_START, 1.0f);
    glFogf(GL_FOG_END, 5.0f);
    glEnable(GL_FOG);


	} // initializeGL()


// called every time the widget is resized
void MainWidget::resizeGL(int w, int h)
	{ // resizeGL()
	// set the viewport to the entire widget
	glViewport(0, 0, w, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
  // perspective projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
  //glFrustum(-9.0,9.0, -6.0, 6.0, 1.5, 30.0);
  gluPerspective(60, (GLfloat)w/(GLfloat)h,1.0,1000.0);

	//glOrtho(-9.0, 9.0, -6.0, 6.0, -6.0, 6.0);
  glMatrixMode(GL_MODELVIEW);

	} // resizeGL()

void MainWidget::grid(int halfGridSize) {

  glBegin(GL_LINES);
  glColor3f(0.0,0.0,0.0);
  for (int i = -halfGridSize; i <= halfGridSize; i++) {
    glVertex3f((float)i,0,(float)-halfGridSize);
    glVertex3f((float)i,0,(float)halfGridSize);
    glVertex3f((float)-halfGridSize,0,(float)i);
    glVertex3f((float)halfGridSize,0,(float)i);
  }
  glEnd();
}

void MainWidget::cube() {
  materialStruct* p_front = &brassMaterials;
  glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);
  glutSolidCube(1.0);
}

// non vbo object and texturing
void MainWidget::earth() {
  glBindTexture(GL_TEXTURE_2D, sptexId);
  glEnable(GL_LIGHTING);
  glEnable(GL_TEXTURE_2D);
  GLUquadricObj *qo = gluNewQuadric();
  gluQuadricDrawStyle(qo,GLU_FILL);
  gluQuadricTexture(qo,GL_TRUE);
  gluSphere(qo, 0.5,20,20);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
}

void MainWidget::drawWorld() {
  glPushMatrix();
  glRotatef(worldAngle, 0.0,1.0,0.0);
  glTranslatef(move[0], move[1], move[2]);
    glPushMatrix();
      glScalef(4.,4.,4.);
      glTranslatef(4.,-2.5,0.);
      glRotatef(90,0.,1.,0.);
      building->draw();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(0.,-2,0.);
      glScalef(2.,2.,2.);
      path->draw();
      floor->draw();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(0.,-1.,0.);
      glScalef(0.5f,0.5f,0.5f);
      glTranslatef(2.,0.,2.);
      box->draw();
      glTranslatef(2.,0.,0.);
      box->draw();
      glTranslatef(-1,2.,0.);
      box->draw();
    glPopMatrix();
    glPushMatrix();
      glScalef(2.0,2.0,2.0);
      glTranslatef(-10.,0.,-13.);
      glRotatef(-50,1.0,0.0,0.0);
      model->draw();
    glPopMatrix();
    glPushMatrix();
      // random bushes around the terrain
      glTranslatef((float)-NUM_BUSHES/2,-4.,(float)-NUM_BUSHES/2);
      for (size_t i = 0; i < NUM_BUSHES; i++) {
        glTranslatef(randomBushPos[0][i], 0.0, randomBushPos[1][i]);
        treeLeaves->draw();
        glTranslatef(-randomBushPos[0][i], 0.0, -randomBushPos[1][i]);
      }
    glPopMatrix();
    //std::cout << move[1] << '\n';
    //this->grid(50);
  glPopMatrix();
}

// called every time the widget needs painting
void MainWidget::paintGL()
	{ // paintGL()
  time_start = glutGet(GLUT_ELAPSED_TIME);
  d_time = time_start - time_old;
  this->movement();

	// clear the widget
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	// You must set the matrix mode to model view directly before enabling the depth test
  glMatrixMode(GL_MODELVIEW);
  glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
  //glEnable(GL_CULL_FACE);
  //glShadeModel(GL_SMOOTH);
  //glShadeModel(GL_FLAT);

  glLoadIdentity();
  // camera
  gluLookAt(0.,2.,5., 0.,0.,0., 0.,1.,0.);

  // change fog density with slider
  glFogf(GL_FOG_DENSITY, fogDens);

  // spin world by angle about the origin
  this->drawWorld();

  //set lighting
	glPushMatrix();
    glLoadIdentity();
    // glTranslatef(move[0], move[1], move[2]);
    GLfloat light0pos[4] = {-1.0f, 1.0f, 1.0f, 0.0f};
    GLfloat light0amb[4] = {0.5f, 0.5f, 0.5f, 0.5f};
    GLfloat light0diff[4] = {0.5f, 0.5f, 0.5f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0diff);
    glEnable(GL_LIGHT0);
	glPopMatrix();

  // earth spinning, circular rotation and sin wave path travel
  glPushMatrix();
    float ypos = 1 * sin((float)((spinnyAngle%360)*(25/360.0)));
    glRotatef(spinnyAngle+=1%360,0.0,1.0,0.0);
    glTranslatef(3,ypos,0.0);
    glRotatef(spinnyAngle%360,1.0,0.0,0.0);
    this->earth();
  glPopMatrix();

  glPushMatrix();
    //get into correct position (so it looks like its on the path)
    glScalef(0.5,0.5,0.5);
    glRotatef(angle,0.,1.,0.);
    glTranslatef(0.0,1.4,0.0);
    //this->cube();
    // decides what animation to use
    if(keyPresses[4]) {
      character->jumping();
    } else if (keyPresses[0]||keyPresses[1]||keyPresses[2]||keyPresses[3]) {
      character->moving();
    } else {
      character->idle();
    }
  glPopMatrix();





	// flush to screen
	glFlush();
  time_old = time_start;

} // paintGL()

  void MainWidget::keyPressEvent(QKeyEvent *pevent) {
    switch (pevent->key()) {
      case Qt::Key_W:
        keyPresses[0] = 1;
        break;
      case Qt::Key_S:
        keyPresses[1] = 1;
        break;
      case Qt::Key_A:
        keyPresses[2] = 1;
        break;
      case Qt::Key_D:
        keyPresses[3] = 1;
        break;
      case Qt::Key_Space:
        keyPresses[4] = 1;
        break;
      default:
        break;
  }
}

void MainWidget::keyReleaseEvent(QKeyEvent *revent) {
  switch (revent->key()) {
    case Qt::Key_W:
      keyPresses[0] = 0;
      break;
    case Qt::Key_S:
      keyPresses[1] = 0;
      break;
    case Qt::Key_A:
      keyPresses[2] = 0;
      break;
    case Qt::Key_D:
      keyPresses[3] = 0;
      break;
    case Qt::Key_Space:
      //
    default:
      break;
  }
}

void MainWidget::movement() {
  float dvelocity = velocity/2;
  if (keyPresses[0]&&keyPresses[2]) {
    move[2] += dvelocity/1000 * d_time;
    move[0] += dvelocity/1000 * d_time;
    angle = 45.0;
  } else if(keyPresses[0]&&keyPresses[3]) {
    move[2] += dvelocity/1000 * d_time;
    move[0] -= dvelocity/1000 * d_time;
    angle = -45.0;
  } else if(keyPresses[1]&&keyPresses[2]) {
    move[2] -= dvelocity/1000 * d_time;
    move[0] += dvelocity/1000 * d_time;
    angle = 135.0;
  } else if(keyPresses[1]&&keyPresses[3]) {
    move[2] -= dvelocity/1000 * d_time;
    move[0] -= dvelocity/1000 * d_time;
    angle = -135.0;
  } else if(keyPresses[0]) {
    move[2] += velocity/1000 * d_time;
    angle = 0.0;
  } else if(keyPresses[1]) {
    move[2] -= velocity/1000 * d_time;
    angle = 180.0;
  } else if(keyPresses[2]) {
    move[0] += velocity/1000 * d_time;
    angle = 90.0;
  } else if(keyPresses[3]) {
    move[0] -= velocity/1000 * d_time;
    angle = -90.0;
  } else {
    //
  }

  // stop at ground - make collision based
  if(move[1]>0.0) {
    move[1] = 0.0;
    keyPresses[4] = 0;
    init_jump_time = 0;
  }

  if(keyPresses[4]) {
    this->jump();
  }
}

void MainWidget::jump() {
  int t = init_jump_time;
  // gravity
  float g = 0.02/1000;
  //initial vertical velocity
  float v = -15.0/1000;

  //calculate vertical displacement
  //v * g * t^2
  float y;
  y = (v*t) + (0.5*(g*(t*t)));
  move[1] = y;
  init_jump_time += d_time;
}
#endif
