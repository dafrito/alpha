#include <cassert>
#include <cstdlib>

#include "QuadGLWidget.h"

const int HALF_RANGE = 200;

QuadGLWidget::QuadGLWidget(QWidget* const parent) :
	GLWidget(parent)
{
	for(int i = 0; i < QuadGLWidget::NUM_QUADS; i++) {
		Quad quad = {
			QVector3D(
				-HALF_RANGE + rand() % (HALF_RANGE * 2),
				-HALF_RANGE + rand() % (HALF_RANGE * 2),
				-10 + rand() % 10),
			QColor(
				rand() % 255,
				rand() % 255,
				rand() % 255),
			rand() % (HALF_RANGE / 4)
		};
		quads << quad;
	}
}

void QuadGLWidget::initializeGL()
{
	GLWidget::initializeGL();
	setZRotation(45);
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
		glVertex3f(x, y, z);
		glVertex3f(x + quad.size, y, z);
		glVertex3f(x + quad.size, y + quad.size, z);
		glVertex3f(x, y + quad.size, z);
	}
	glEnd();
}
