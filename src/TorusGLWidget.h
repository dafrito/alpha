#ifndef TORUSGLWIDGET_H
#define TORUSGLWIDGET_H

#include "GLWidget.h"
#include <cassert>
#include <cmath>

class TorusGLWidget : public GLWidget
{
public:
	TorusGLWidget(QWidget* parent = 0);
	~TorusGLWidget();
protected:
	void initializeGL();
	void render();
};

TorusGLWidget::TorusGLWidget(QWidget* parent) : GLWidget(parent) {}

void renderTorus();

void TorusGLWidget::initializeGL()
{
	GLWidget::initializeGL();
	setXRotation(90);

	glNewList(1, GL_COMPILE);
	renderTorus();
	glEndList();
}

void Circlef (float radius,float vertices = 40) {
    glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= vertices; i++) {
		const float angle = i * 2 * (3.14159 / (float) vertices);
		glVertex2f(
			radius * (float) sin(angle),
			radius * (float) cos(angle)
		);
	}
    glEnd();
}

#include <QDebug>

void renderTorus()
{
	// How many circles are rendered.
	const int SLICES = 360;
	assert(SLICES >= 5); // We need at least one slice per color group, else PARTITION is zero.

	// How many circles for each color transition.
	const int PARTITION = SLICES / 5;

	const float ANGLE_PER_SLICE = (float) 360 / SLICES;
	for (int i = 0; i < SLICES; i++) {
		glPushMatrix();
		{
			glRotatef(ANGLE_PER_SLICE * i, 0, 1, 0);
			const float slice = i % PARTITION;
			// inc and dec are both guaranteed to be [0, 1].
			const float inc = slice / PARTITION;
			const float dec = 1 - inc;
			if (i < PARTITION) {
				// Purple to red
				glColor3f(1, 0, dec);
			} else if (i < 2 * PARTITION) {
				// Red to yellow
				glColor3f(1, inc, 0);
			} else if (i < 3 * PARTITION) {
				// Yellow to green
				glColor3f(dec, 1, 0);
			} else if (i < 4 * PARTITION) {
				// Green to blue
				glColor3f(0, dec, inc);
			} else {
				// Blue to purple
				glColor3f(inc, 0, 1);
			}
			glTranslatef(50,0,0);
			Circlef(30,40);
		}
		glPopMatrix();
	}
}

void TorusGLWidget::render()
{
	glCallList(1);
}

TorusGLWidget::~TorusGLWidget()
{
	glDeleteLists(1, 1);
}

#endif // TORUSGLWIDGET_H
