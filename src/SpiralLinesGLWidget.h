#ifndef SPIRALLINESGLWIDGET_H
#define SPIRALLINESGLWIDGET_H

#include "GLWidget.h"
#include <cmath>

class SpiralLinesGLWidget : public GLWidget
{
public:
	SpiralLinesGLWidget(QWidget* parent = 0);
protected:
	void initializeGL();
	void render();
};

SpiralLinesGLWidget::SpiralLinesGLWidget(QWidget* parent) : GLWidget(parent) {}

void SpiralLinesGLWidget::initializeGL()
{
	GLWidget::initializeGL();
	setXRotation(-45);
	setYRotation(15);
	setZRotation(45);
}

void SpiralLinesGLWidget::render()
{
	// How many revolutions of the spiral are rendered.
	static const float REVOLUTIONS = 10;
	static const float PI = 3.14159;

	// How many vertices per revolution.
	static const float SLICES = 40;

	static const float DEPTH = 50;

	glBegin(GL_LINE_STRIP);
	float z=-50;
	for (int i = 0; i <= REVOLUTIONS * SLICES; i++) {
		const float angle = i * 2 * PI / SLICES;
		glVertex3f(
			angle * (float) sin(angle),
			angle * (float) cos(angle),
			z);
		z += DEPTH / (REVOLUTIONS * SLICES);
	}
	glEnd();
}

#endif // SPIRALLINESGLWIDGET_H
