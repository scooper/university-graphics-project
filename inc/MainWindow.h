#ifndef __GL_POLYGON_WINDOW_H__
#define __GL_POLYGON_WINDOW_H__ 1

#include <QGLWidget>
#include <QMenuBar>
#include <QSlider>
#include <QPushButton>
#include <QBoxLayout>
#include <QTimer>
#include <QLabel>
#include <QSpinBox>
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
	QHBoxLayout *fogLayout;
	QHBoxLayout *worldLayout;

	// beneath that, the main widget
	MainWidget *mainWidget;

	QTimer *timer;
	// and a slider for the number of vertices
	QLabel *fogLabel;
	QSlider *fogSlider;
	QLabel *worldLabel;
	QSlider *worldSlider;
	QPushButton *randomBushesButton;
	QSpinBox *worldAngleValue;
	// resets all the interface elements
	void ResetInterface();
	};

#endif
