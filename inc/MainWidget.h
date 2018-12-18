#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <QGLWidget>
#include <QKeyEvent>
#include "Model.h"

class MainWidget: public QGLWidget
	{ //

	Q_OBJECT

	public:
	MainWidget(QWidget *parent);


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

	int keyPresses[5] = {0, 0, 0, 0, 0};
	int init_jump_time = 0;
	int d_time;
	int time_start;
	int time_old;
	float velocity = 8.0;
	float angle = 0.0;
	float move[3] = {0.0,0.0,0.0};

	Model* model;
	//void polygon(int, int, int, int);

	}; // class GLPolygonWidget

#endif
