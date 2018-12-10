#include "MainWindow.h"

// constructor / destructor
MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
	{ // constructor

	// create menu bar
	menuBar = new QMenuBar(this);


	// create the action
	actionQuit = new QAction("&Quit", this);

	// leave signals & slots to the controller

	// create the window layout
	windowLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

	// create main widget
	mainWidget = new MainWidget(this);
	windowLayout->addWidget(mainWidget);

	timer = new QTimer();
	connect(timer, SIGNAL(timeout()), mainWidget, SLOT(update()));
	timer->start(1000/30);

	// create slider
	//nVerticesSlider = new QSlider(Qt::Horizontal);
	//windowLayout->addWidget(nVerticesSlider);
	} // constructor

MainWindow::~MainWindow()
	{ // destructor
	delete mainWidget;
	delete windowLayout;
	delete actionQuit;
	delete menuBar;
	} // destructor

// resets all the interface elements
void MainWindow::ResetInterface()
	{ // ResetInterface()
	//nVerticesSlider->setMinimum(3);
	//nVerticesSlider->setMaximum(30);

	//don't use the slider for now

	//	nVerticesSlider->setValue(thePolygon->nVertices);

	// now force refresh
	mainWidget->update();
	update();
	} // ResetInterface()
