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
	static const float PI = 3.14159;

	glBegin(GL_LINE_STRIP);
	for (float angle = 0; angle < PI*20 ; angle +=  PI / 200.0f) {
		glVertex2f(
			angle * (float) sin(angle),
			angle * (float) cos(angle));
	}
	glEnd();
}

#endif // SPIRALLINESGLWIDGET_H
