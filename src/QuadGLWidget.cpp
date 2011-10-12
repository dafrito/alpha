#include <cassert>
#include <cstdlib>

#include "QuadGLWidget.h"

const int HALF_RANGE = 200;
const int MAX_VELOCITY = 3;
const double GRAVITY = 3;

QuadGLWidget::QuadGLWidget(QWidget* const parent) :
	AnimatedGLWidget(parent)
{
	for(int i = 0; i < QuadGLWidget::NUM_QUADS; i++) {
		const int size = 1 + rand() % (HALF_RANGE / 7);
		Quad quad = {
			QVector3D(
				-HALF_RANGE + size + rand() % ((HALF_RANGE - size) * 2),
				-HALF_RANGE + size + rand() % ((HALF_RANGE - size) * 2),
				-HALF_RANGE + size + rand() % ((HALF_RANGE - size) * 2)),
			QColor(
				rand() % 255,
				rand() % 255,
				rand() % 255),
			size,
			QVector3D(
				-MAX_VELOCITY + rand() % (MAX_VELOCITY * 2),
				-MAX_VELOCITY + rand() % (MAX_VELOCITY * 2),
				0)
		};
		quads << quad;
	}
}

void QuadGLWidget::tick(const float& elapsed)
{
	static const QVector3D VEC_X(-1, 1, 1);
	static const QVector3D VEC_Y(1, -1, 1);
	AnimatedGLWidget::tick(elapsed);
	for (QList<Quad>::iterator q = quads.begin(); q != quads.end(); ++q) {
		const int range = HALF_RANGE - q->size;
		{
			double x = q->pos.x() + q->velocity.x();
			const double diff = abs(x) - range;
			if (diff > 0) {
				q->velocity *= VEC_X;
				if (x > 0) {
					// X is positive; head negative
					x = range - diff;
				} else {
					// X is negative; head positive
					x = -range + diff;
				}
			}
			q->pos.setX(x);
		}
		{
			double y = q->pos.y() + q->velocity.y();
			const double diff = abs(y) - range;
			if (diff > 0) {
				q->velocity *= VEC_Y;
				if (y > 0) {
					// Y is positive; head negative
					y = range - diff;
				} else {
					// Y is negative; head positive
					y = -range + diff;
				}
			}
			q->pos.setY(y);
		}
		q->velocity.setY(q->velocity.y() - GRAVITY * elapsed);
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
