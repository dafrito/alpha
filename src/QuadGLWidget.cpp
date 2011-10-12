#include <cassert>
#include <cstdlib>

#include "QuadGLWidget.h"

const int HALF_RANGE = 200;

QuadGLWidget::QuadGLWidget(QWidget* const parent) :
	GLWidget(parent)
{
	for(int i = 0; i < QuadGLWidget::NUM_QUADS; i++) {
		const int size = 1 + rand() % (HALF_RANGE / 7);
		Quad quad = {
			QVector3D(
				-HALF_RANGE + size + rand() % ((HALF_RANGE - size) * 2),
				-HALF_RANGE + size + rand() % ((HALF_RANGE - size) * 2),
				-10 + rand() % 10),
			QColor(
				rand() % 255,
				rand() % 255,
				rand() % 255),
			size
		};
		quads << quad;
	}
}

void QuadGLWidget::render()
{
	glBegin(GL_QUADS);

	for (QList<Quad>::const_iterator quadIter = quads.begin(); quadIter != quads.end(); ++quadIter) {
		const Quad quad = *quadIter;
		glColor3f(quad.color.redF(), quad.color.greenF(), quad.color.blueF());
		const double x = quad.pos.x();
		const double y = quad.pos.y();
		const double z = quad.pos.z();
		glVertex3f(x - quad.size, y - quad.size, z);
		glVertex3f(x + quad.size, y - quad.size, z);
		glVertex3f(x + quad.size, y + quad.size, z);
		glVertex3f(x - quad.size, y + quad.size, z);
	}
	glEnd();
}

void QuadGLWidget::resizeGL(int width, int height)
{
	int side = qMin(width, height);
	glViewport((width - side) / 2, (height - side) / 2, side, side);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(
		-HALF_RANGE, HALF_RANGE,
		-HALF_RANGE, HALF_RANGE,
		-HALF_RANGE, HALF_RANGE);
	glMatrixMode(GL_MODELVIEW);
}
