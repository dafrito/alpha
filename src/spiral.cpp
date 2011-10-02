#include <QApplication>
#include <QDesktopWidget>

#include "GLDemo.h"
#include <cmath>

class SpiralGLDemo : public GLDemo
{
	void render();
public:
	SpiralGLDemo();
};

SpiralGLDemo::SpiralGLDemo()
{
	setXRotation(-45);
	setYRotation(15);
	setZRotation(45);
}

void SpiralGLDemo::render()
{
	// How many revolutions of the spiral are rendered.
	static const int REVOLUTIONS = 4;
	static const float PI = 3.14159;

	glBegin(GL_POINTS);
	float z = -50.0;
	for (float angle = 0; angle <= REVOLUTIONS * 2 * PI; angle += 0.1f) {
		float x = 50.0f * (float) sin(angle);
		float y = 50.0f * (float) cos(angle);
		glVertex3f(x, y, z);
		z += 0.5f;
	}
	glEnd();
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	SpiralGLDemo demo;
	setup_demo(demo);
	return app.exec();
}
