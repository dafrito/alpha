#include <QApplication>
#include <QDesktopWidget>

#include "DemoTabWidget.h"
#include "SpiralGLWidget.h"
#include "SpiralLinesGLWidget.h"
#include "BlankGLWidget.h"
#include "RotatableGLDemo.h"
#include "LogoGLWidget.h"
#include "PlanetsGLWidget.h"
#include "TriangleGLWidget.h"
#include "TriangleStripGLWidget.h"
#include "StippleGLWidget.h"
#include "RandomStippleGLWidget.h"
#include "DiamondGLDemo.h"
#include "CubeGLWidget.h"
#include "StarGLDemo.h"
#include "TorusGLWidget.h"
#include "CylinderGLWidget.h"

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	QApplication app(argc, argv);
	QSize appSize(800, 600);

	DemoTabWidget demoStack;
	demoStack.resize(appSize);

	BlankGLWidget blankDemo;
	demoStack.addTab(&blankDemo, "Blank");

	TriangleGLWidget triangleDemo;
	demoStack.addTab(&triangleDemo, "Triangle");

	TriangleStripGLWidget triangleStripDemo;
	demoStack.addTab(&triangleStripDemo, "Triangle Strip");	

	StarGLDemo starDemo;
	demoStack.addTab(&starDemo, "Star");

	RotatableGLDemo cylinderDemo(new CylinderGLWidget);
	demoStack.addTab(&cylinderDemo, "Cylinder");

	RotatableGLDemo spiralDemo(new SpiralGLWidget);
	demoStack.addTab(&spiralDemo, "3D Spiral");

	RotatableGLDemo spiralLinesDemo(new SpiralLinesGLWidget);
	demoStack.addTab(&spiralLinesDemo, "Spiral");

	RotatableGLDemo torusDemo(new TorusGLWidget);
	demoStack.addTab(&torusDemo, "Torus");

	RotatableGLDemo planetsDemo(new PlanetsGLWidget);
	demoStack.addTab(&planetsDemo, "Planets");

	RotatableGLDemo stippleDemo(new StippleGLWidget);
	demoStack.addTab(&stippleDemo, "Stipple");

	RotatableGLDemo randomStippleDemo(new RandomStippleGLWidget);
	demoStack.addTab(&randomStippleDemo, "Random Stipple");

	RotatableGLDemo cubeDemo(new CubeGLWidget);
	demoStack.addTab(&cubeDemo, "Cubes");

	RotatableGLDemo logoDemo(new LogoGLWidget);
	demoStack.addTab(&logoDemo, "Logo");

	DiamondGLDemo diamondDemo;
	demoStack.addTab(&diamondDemo, "Diamond");

	// Display most recently added tab.
	demoStack.setCurrentIndex(demoStack.count() -1);

	QDesktopWidget* desktop = QApplication::desktop();

	int desktopArea = desktop->width() * desktop->height();
	int appArea = appSize.width() * appSize.height();
	if (((float)appArea / (float)desktopArea) > 0.75f) {
		// Just maximize it if the desktop isn't significantly
		// bigger than our app's area.
		demoStack.showMaximized();
	} else {
		// Center the app on the primary monitor.
		QPoint windowLocation = desktop->screenGeometry(desktop->primaryScreen()).center();
		windowLocation.setX(windowLocation.x() - appSize.width() / 2);
		windowLocation.setY(windowLocation.y() - appSize.height() / 2);
		demoStack.move(windowLocation);
		demoStack.show();
	}

	return app.exec();
}
