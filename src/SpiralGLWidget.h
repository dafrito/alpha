#ifndef SPIRALGLWIDGET_H
#define SPIRALGLWIDGET_H

#include "GLWidget.h"
#include <cmath>

class SpiralGLWidget : public GLWidget
{
protected:
	void initializeGL();
	void render();
};

void SpiralGLWidget::initializeGL()
{
	GLWidget::initializeGL();
	setXRotation(-45);
	setYRotation(15);
	setZRotation(45);
}

void SpiralGLWidget::render()
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

#endif // SPIRALGLWIDGET_H
