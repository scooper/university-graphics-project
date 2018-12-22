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

	// set fps limit
	timer = new QTimer();
	connect(timer, SIGNAL(timeout()), mainWidget, SLOT(update()));
	timer->start(1000/60);


	// create slider
	fogLayout = new QHBoxLayout();
	fogLabel = new QLabel();
	fogLayout->addWidget(fogLabel);
	fogLabel->setText("Fog Density");
	fogSlider = new QSlider(Qt::Horizontal);
	fogSlider->setRange(0,100);
	fogLayout->addWidget(fogSlider);
	windowLayout->addLayout(fogLayout);


	worldLayout = new QHBoxLayout();
	worldLabel = new QLabel();
	worldLabel->setText("World Angle");
	worldSlider = new QSlider(Qt::Horizontal);
	worldSlider->setRange(0, 360);
	worldAngleValue = new QSpinBox();
	worldAngleValue->setRange(0,360);
	worldLayout->addWidget(worldLabel);
	worldLayout->addWidget(worldSlider);
	worldLayout->addWidget(worldAngleValue);

	windowLayout->addLayout(worldLayout);

	randomBushesButton = new QPushButton("Randomize Bush Positions");
	windowLayout->addWidget(randomBushesButton);

	connect(fogSlider, SIGNAL(valueChanged(int)), mainWidget, SLOT(setFogDensity(int)));
	connect(randomBushesButton, SIGNAL(clicked()), mainWidget, SLOT(randomizeBushes()));
	connect(worldSlider, SIGNAL(valueChanged(int)), mainWidget, SLOT(setWorldAngle(int)));
	connect(worldSlider, SIGNAL(valueChanged(int)), worldAngleValue, SLOT(setValue(int)));
	connect(worldAngleValue, SIGNAL(valueChanged(int)), worldSlider, SLOT(setValue(int)));
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
