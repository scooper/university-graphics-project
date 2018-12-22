#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <QGLWidget>
#include <QKeyEvent>
#include "Model.h"
#include "Character.h"

class MainWidget: public QGLWidget
	{ //

	Q_OBJECT

	public:
	MainWidget(QWidget *parent);

	public slots:
	void randomizeBushes();
	void setFogDensity(int value);
	void setWorldAngle(int value);


	protected:
	// called when OpenGL context is set up
	void initializeGL();
	// called every time the widget is resized
	void resizeGL(int w, int h);
	// called every time the widget needs painting
	void paintGL();

	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

	private:

	void cube();
	void movement();
	void grid(int halfGridSize);
	void jump();
	void drawWorld();
	void earth();

	GLuint sptexId;

	int keyPresses[5] = {0, 0, 0, 0, 0};
	int init_jump_time = 0;
	int d_time;
	int time_start;
	int time_old;
	float velocity = 10.0;
	float angle = 0.0;
	float move[3] = {0.0,0.0,0.0};

	float fogDens;
	int worldAngle;
	int spinnyAngle = 0;

	Model* model;
	Model* floor;
	Model* path;
	Model* box;
	Model* sky;
	Model* treeTrunk;
	Model* treeLeaves;
	Model *building;
	Character* character;

	static const int NUM_BUSHES = 100;
	float randomBushPos[2][NUM_BUSHES] = {0};
	//void polygon(int, int, int, int);

	}; // class GLPolygonWidget

#endif
