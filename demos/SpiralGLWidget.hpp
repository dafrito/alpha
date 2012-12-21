#ifndef SPIRALGLWIDGET_H
#define SPIRALGLWIDGET_H

#include "GLWidget.hpp"
#include <cmath>

class SpiralGLWidget : public GLWidget
{
public:
	SpiralGLWidget(QWidget* parent = 0);
protected:
	void initializeGL();
	void render();
};

SpiralGLWidget::SpiralGLWidget(QWidget* parent) : GLWidget(parent) {}

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
	static const float SLICES = 36 * 8;
	static const float LENGTH = 125;

	glBegin(GL_POINTS);
	float z = -50.0;
	for (int i = 0; i <= SLICES * REVOLUTIONS; ++i) {
		float angle = (float)i * 2 * PI / SLICES;
		float x = 50.0f * (float) sin(angle);
		float y = 50.0f * (float) cos(angle);
		glVertex3f(x, y, z);
		z += LENGTH / (REVOLUTIONS * SLICES);
	}
	glEnd();
}

#endif // SPIRALGLWIDGET_H
