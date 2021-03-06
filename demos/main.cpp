#include <QApplication>
#include <QDesktopWidget>

#include "DemoTabWidget.hpp"
#include "SpiralGLWidget.hpp"
#include "SpiralLinesGLWidget.hpp"
#include "BlankGLWidget.hpp"
#include "RotatableGLDemo.hpp"
#include "LogoGLWidget.hpp"
#include "PlanetsGLWidget.hpp"
#include "TriangleGLWidget.hpp"
#include "TriangleStripGLWidget.hpp"
#include "StippleGLWidget.hpp"
#include "RandomStippleGLWidget.hpp"
#include "DiamondGLDemo.hpp"
#include "CubeGLWidget.hpp"
#include "StarGLDemo.hpp"
#include "TorusGLWidget.hpp"
#include "FilmRollGLWidget.hpp"
#include "VehicleGLWidget.hpp"
#include "FontGLWidget.hpp"
#include "LuaGLDemo.hpp"

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

	RotatableGLDemo filmRollDemo(new FilmRollGLWidget);
	demoStack.addTab(&filmRollDemo, "Film Roll");

	RotatableGLDemo spiralDemo(new SpiralGLWidget);
	demoStack.addTab(&spiralDemo, "3D Spiral");

	RotatableGLDemo spiralLinesDemo(new SpiralLinesGLWidget);
	demoStack.addTab(&spiralLinesDemo, "Spiral");

	LuaGLDemo luaDemo;
	demoStack.addTab(&luaDemo, "Lua");

	RotatableGLDemo torusDemo(new TorusGLWidget);
	demoStack.addTab(&torusDemo, "Torus");

	RotatableGLDemo planetsDemo(new PlanetsGLWidget);
	demoStack.addTab(&planetsDemo, "Planets");

	RotatableGLDemo stippleDemo(new StippleGLWidget);
	demoStack.addTab(&stippleDemo, "Stipple");

	RotatableGLDemo randomStippleDemo(new RandomStippleGLWidget);
	demoStack.addTab(&randomStippleDemo, "Random Stipple");

	RotatableGLDemo fontDemo(new FontGLWidget);
	demoStack.addTab(&fontDemo, "Fonts");

	RotatableGLDemo cubeDemo(new CubeGLWidget);
	demoStack.addTab(&cubeDemo, "Cubes");

	RotatableGLDemo logoDemo(new LogoGLWidget);
	demoStack.addTab(&logoDemo, "Logo");

	DiamondGLDemo diamondDemo;
	demoStack.addTab(&diamondDemo, "Diamond");

	VehicleGLWidget vehicleDemo;
	demoStack.addTab(&vehicleDemo, "Vehicle");

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
