#include <QApplication>
#include <QDesktopWidget>
#include <QTabWidget>

#include "SpiralGLDemo.h"
#include "BlankGLDemo.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QSize appSize(800, 600);

	QTabWidget demoStack;
	demoStack.resize(appSize);

	BlankGLDemo blankDemo;
	demoStack.addTab(&blankDemo, "Blank");

	SpiralGLDemo spiralDemo;
	demoStack.addTab(&spiralDemo, "Spiral");

	demoStack.show();

	return app.exec();
}
