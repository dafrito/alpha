#ifndef FILMROLLGLWIDGET_H
#define FILMROLLGLWIDGET_H

#include "GLWidget.hpp"
#include <cmath>

class FilmRollGLWidget : public GLWidget
{
public:
	FilmRollGLWidget(QWidget* parent = 0) : GLWidget(parent) {}
protected:
	void render();
};

static const int SLICES = 80; // Slices per revolution
static const int RADIUS = 25;
static const float LENGTH = 10;
static const float REVOLUTIONS = 10;

void FilmRollGLWidget::render()
{
	static const float PI = 3.14159;
	static const float SLICE_ANGLE = 2 * PI / SLICES;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <= REVOLUTIONS * SLICES; ++i) {
		glVertex3f(
			log(i) * RADIUS * cos(i * SLICE_ANGLE),
			log(i) * RADIUS * sin(i * SLICE_ANGLE),
			LENGTH / 2);
		glVertex3f(
			log(i) * RADIUS * cos(i * SLICE_ANGLE),
			log(i) * RADIUS * sin(i * SLICE_ANGLE),
			-LENGTH / 2);
	}
	glEnd();
}

#endif // FILMROLLGLWIDGET_H
