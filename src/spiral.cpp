#include <QApplication>

#include "SpiralGLDemo.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	SpiralGLDemo demo;
	setup_demo(demo);
	return app.exec();
}
