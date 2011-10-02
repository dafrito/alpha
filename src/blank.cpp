#include <QApplication>
#include <QDesktopWidget>

#include "GLDemo.h"

class BlankGLDemo : public GLDemo
{
	void render();
};

void BlankGLDemo::render()
{
	// If there was rendering to be done, it would
	// be done here.
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	BlankGLDemo demo;
	setup_demo(demo);
	return app.exec();
}
