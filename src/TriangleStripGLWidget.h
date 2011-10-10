#ifndef TRIANGLESTRIPGLWIDGET_H
#define TRIANGLESTRIPGLWIDGET_H

#include "GLWidget.h"
#include <cmath>

/**
 * Draws a trapezoid on screen using a triangle strip. Strips can be thought of
 * lists of vertices, where each triangle in the list is composed of some
 * adjacent group of three vertices. The vertices are colored for easy viewing.
 * 
 * @author Aaron Faanes, ported by Brett Langford
 * 
 */

class TriangleStripGLWidget : public GLWidget
{
public:
	TriangleStripGLWidget(QWidget* parent = 0);
protected:
	void initializeGL();
	void render();
};

TriangleStripGLWidget::TriangleStripGLWidget(QWidget* parent) : GLWidget(parent) {}

void TriangleStripGLWidget::initializeGL()
{
	GLWidget::initializeGL();
}

void TriangleStripGLWidget::render()
{
	glBegin(GL_TRIANGLE_STRIP);

	glColor3f(1, 0, 0);
	glVertex2f(0, 0);

	glColor3f(1, 1, 0);
	glVertex2f(50, 0);

	glColor3f(0, 1, 0);
	glVertex2f(25, 50);

	glColor3f(0, 1, 1);
	glVertex2f(75, 50);

	glColor3f(0, 0, 1);
	glVertex2f(50, 100);

	glEnd();
}

#endif // TRIANGLESTRIPGLWIDGET_H
