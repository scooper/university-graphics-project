#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES
#include <GL/glu.h>
#include <GL/glut.h>
#include <QGLWidget>
#include <QKeyEvent>
#include <iostream>
#include "MainWidget.h"



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

static materialStruct whiteShinyMaterials = {
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  100.0
};


// constructor
MainWidget::MainWidget(QWidget *parent)
	: QGLWidget(parent)
	{ // constructor
    setFocusPolicy(Qt::ClickFocus);
	} // constructor

// called when OpenGL context is set up
void MainWidget::initializeGL()
	{ // initializeGL()


    // set the widget background colour
    glClearColor(0.4, 0.4, 0.9, 0.0);
    model = new Model("models/shape.obj");

	} // initializeGL()


// called every time the widget is resized
void MainWidget::resizeGL(int w, int h)
	{ // resizeGL()
	// set the viewport to the entire widget
	glViewport(0, 0, w, h);

  // apply lighting
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
  // perspective projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
  //glFrustum(-9.0,9.0, -6.0, 6.0, 1.5, 30.0);
  gluPerspective(60, (GLfloat)w/(GLfloat)h,1.0,100.0);

  // glMatrixMode(GL_MODELVIEW);
	//glOrtho(-9.0, 9.0, -6.0, 6.0, -6.0, 6.0);

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
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
    glLoadIdentity();
    GLfloat light_pos[] = {0., 0., 10., 1.};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightf (GL_LIGHT0, GL_SPOT_CUTOFF,15.);
	glPopMatrix();

  glPushMatrix();
    //glTranslatef(0.0,2.0,0.0);
  glPopMatrix();

  glPushMatrix();
    glRotatef(angle,0.,1.,0.);
    //this->cube();
    model->draw();
  glPopMatrix();
  glPushMatrix();
    //std::cout << move[1] << '\n';
    glTranslatef(move[0], move[1], move[2]);
    glTranslatef(0.,-1,0.);
    this->grid(50);
  glPopMatrix();

  glLoadIdentity();
  // camera
  gluLookAt(0.,2.,5., 0.,0.,0., 0.,1.,0.);


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
