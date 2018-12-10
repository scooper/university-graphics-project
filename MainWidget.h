#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <QGLWidget>
#include <QKeyEvent>

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

	private:

	void cube();
	void move();

	int keyPresses[]
	int time_start;
	int time_old;
	int d_time;
	float velocity = 1.0;
	float angle = 0.0;
	float xmove = 0.0;
	float zmove = 0.0;
	//void polygon(int, int, int, int);

	}; // class GLPolygonWidget

#endif
