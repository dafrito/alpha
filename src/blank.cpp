#include <QApplication>
#include <QDesktopWidget>

#include "BlankGLDemo.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	BlankGLDemo demo;
	setup_demo(demo);
	return app.exec();
}
