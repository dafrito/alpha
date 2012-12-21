#include "StarGLWidget.hpp"

#include <QtGui>
#include <QtOpenGL>
#include <cmath>

StarGLWidget::StarGLWidget(QWidget* const parent) :
	GLWidget(parent),
	showingInsignificantEdges(true)
{
}

void StarGLWidget::render()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glPushMatrix();
	glTranslatef(0, 20, 0);

	glBegin(GL_TRIANGLES);

	// Top triangle
	glEdgeFlag(showingInsignificantEdges);
	glColor3ub(255, 255, 255);
	glVertex2f(-20, 0);
	glEdgeFlag(true);
	glVertex2f(20, 0);
	glColor3ub(255, 0, 0);
	glVertex2f(0, 40);
	glColor3ub(255, 255, 255);

	// Left triangle
	glVertex2f(-20, 0);
	glColor3ub(0, 0, 255);
	glVertex2f(-60, -20);
	glColor3ub(255, 255, 255);
	glEdgeFlag(showingInsignificantEdges);
	glVertex2f(-20, -40);
	glEdgeFlag(true);

	// Bottom triangle
	glVertex2f(-20, -40);
	glColor3ub(0, 255, 0);
	glVertex2f(0, -80);
	glColor3ub(255, 255, 255);
	glEdgeFlag(showingInsignificantEdges);
	glVertex2f(20, -40);
	glEdgeFlag(true);

	// Right triangle
	glVertex2f(20, -40);
	glColor3ub(255, 255, 0);
	glVertex2f(60, -20);
	glColor3ub(255, 255, 255);
	glEdgeFlag(showingInsignificantEdges);
	glVertex2f(20, 0);
	glEdgeFlag(true);

	// Interior box
	glEdgeFlag(showingInsignificantEdges);
	glVertex2f(-20, 0);
	glVertex2f(-20, -40);
	glVertex2f(20, 0);
	glVertex2f(-20, -40);
	glVertex2f(20, -40);
	glVertex2f(20, 0);
	glEdgeFlag(true);

	glEnd();
	glPopMatrix();

	for (int i = 0; i < 5; ++i) {
		glTranslatef(0, 0, -10);
		glColor3ub(255 - i*50, 0, 255 - i*50);
		glBegin(GL_QUADS);
		glVertex2f(-20, -20);
		glVertex2f(20, -20);
		glVertex2f(20, 20);
		glVertex2f(-20, 20);
		glEnd();
	}
}
