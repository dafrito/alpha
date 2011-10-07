#include <QtGui>
#include <QtOpenGL>
#include <cmath>

#include "StarGLWidget.h"

StarGLWidget::StarGLWidget(QWidget* const parent) :
	GLWidget(parent),
	showingInsignificantEdges(true)
{
}

void StarGLWidget::render()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glTranslatef(0, 20, 0);

	glBegin(GL_TRIANGLES);

	glEdgeFlag(showingInsignificantEdges);
	glVertex2f(-20, 0);
	glEdgeFlag(true);
	glVertex2f(20, 0);
	glVertex2f(0, 40);

	glVertex2f(-20, 0);
	glVertex2f(-60, -20);
	glEdgeFlag(showingInsignificantEdges);
	glVertex2f(-20, -40);
	glEdgeFlag(true);

	glVertex2f(-20, -40);
	glVertex2f(0, -80);
	glEdgeFlag(showingInsignificantEdges);
	glVertex2f(20, -40);
	glEdgeFlag(true);

	glVertex2f(20, -40);
	glVertex2f(60, -20);
	glEdgeFlag(showingInsignificantEdges);
	glVertex2f(20, 0);
	glEdgeFlag(true);

	glEdgeFlag(showingInsignificantEdges);
	glVertex2f(-20, 0);
	glVertex2f(-20, -40);
	glVertex2f(20, 0);

	glVertex2f(-20, -40);
	glVertex2f(20, -40);
	glVertex2f(20, 0);
	glEdgeFlag(true);

	glEnd();
}
