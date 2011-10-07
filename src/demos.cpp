#include <QApplication>
#include <QDesktopWidget>

#include "DemoTabWidget.h"
#include "SpiralGLWidget.h"
#include "BlankGLWidget.h"
#include "LogoGLDemo.h"
#include "AtomGLWidget.h"
#include "TriangleGLWidget.h"
#include "RandomStippleGLWidget.h"
#include "DiamondGLDemo.h"
#include "QuadGLWidget.h"

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

	SpiralGLWidget spiralDemo;
	demoStack.addTab(&spiralDemo, "Spiral");

	AtomGLWidget atomDemo;
	demoStack.addTab(&atomDemo, "Atoms");

	RandomStippleGLWidget randomStippleDemo;
	demoStack.addTab(&randomStippleDemo, "Random Stipple");

	QuadGLWidget quadDemo;
	demoStack.addTab(&quadDemo, "Quad");

	LogoGLDemo logoDemo;
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
