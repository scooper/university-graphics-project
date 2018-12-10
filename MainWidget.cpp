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
	glClearColor(0.3, 0.3, 0.3, 0.0);



	} // initializeGL()


// called every time the widget is resized
void MainWidget::resizeGL(int w, int h)
	{ // resizeGL()
	// set the viewport to the entire widget
	glViewport(0, 0, w, h);

  // apply lighting
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat light_pos[] = {0., 0., 10., 1.};
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
  //glLightf (GL_LIGHT0, GL_SPOT_CUTOFF,20.);



  // perspective projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
  //glFrustum(-9.0,9.0, -6.0, 6.0, 1.5, 30.0);
  gluPerspective(60, (GLfloat)w/(GLfloat)h,1.0,100.0);

  // glMatrixMode(GL_MODELVIEW);
	//glOrtho(-9.0, 9.0, -6.0, 6.0, -6.0, 6.0);

	} // resizeGL()


void MainWidget::cube(){

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
  this->move();
	// clear the widget
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// You must set the matrix mode to model view directly before enabling the depth test

	glEnable(GL_DEPTH_TEST); // comment out depth test to observe the result


	// glPushMatrix();
	// glLoadIdentity();
  //       GLfloat light_pos[] = {0., 0., 10., 1.};
  //       glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
  //       glLightf (GL_LIGHT0, GL_SPOT_CUTOFF,15.);
	// glPopMatrix();



  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
    glTranslatef(xmove, 0.0, zmove);
    this->cube();
  glPopMatrix();
  glPushMatrix();
    glTranslatef(0.,-1.,0.);
    glScalef(20.,1.,20.);
    this->cube();
  glPopMatrix();

	glLoadIdentity();

  // camera
  gluLookAt(0.,2.,5., 0.,0.,0., 0.,1.,0.);


	// flush to screen
	glFlush();
  time_old = time_start;
	} // paintGL()

  void MainWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
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
      default:
        break;
    }
  }

  void MainWidget::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
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
      default:
        break;
    }
  }

  void MainWidget::move() {
    if (keyPresses[0]&&keyPresses[2]) {
      zmove -= velocity/1000 * d_time;
      xmove -= velocity/1000 * d_time;
    } else if(keyPresses[0]&&keyPresses[3]) {
      zmove -= velocity/1000 * d_time;
      xmove += velocity/1000 * d_time;
    } else if(keyPresses[1]&&keyPresses[2]) {
      zmove += velocity/1000 * d_time;
      xmove -= velocity/1000 * d_time;
    } else if(keyPresses[1]&&keyPresses[3]) {
      zmove += velocity/1000 * d_time;
      xmove += velocity/1000 * d_time;
    } else if(keyPresses[0]) {
      zmove -= velocity/1000 * d_time;
    } else if(keyPresses[1]) {
      zmove += velocity/1000 * d_time;
    } else if(keyPresses[2]) {
      xmove -= velocity/1000 * d_time;
    } else if(keyPresses[3]) {
      xmove += velocity/1000 * d_time;
    }
  }
