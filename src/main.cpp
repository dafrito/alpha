#include <QApplication>
#include <QDesktopWidget>

#include "GLDemo.h"

class BlankDemo : public GLDemo
{
	void render();
};

void BlankDemo::render()
{
	// If there was rendering to be done, it would
	// be done here.
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	BlankDemo window;
	setup_demo(window);
	return app.exec();
}
