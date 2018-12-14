#ifndef __GL_POLYGON_WINDOW_H__
#define __GL_POLYGON_WINDOW_H__ 1

#include <QGLWidget>
#include <QMenuBar>
#include <QSlider>
#include <QBoxLayout>
#include <QTimer>
#include "MainWidget.h"

class MainWindow: public QWidget
	{
	public:


	// constructor / destructor
	MainWindow(QWidget *parent);
	~MainWindow();

	// visual hierarchy
	// menu bar
	QMenuBar *menuBar;
	// quit action
	QAction *actionQuit;

	// window layout
	QBoxLayout *windowLayout;

	// beneath that, the main widget
	MainWidget *mainWidget;

	QTimer *timer;
	// and a slider for the number of vertices
	//QSlider *nVerticesSlider;

	// resets all the interface elements
	void ResetInterface();
	};

#endif
