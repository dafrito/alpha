#include <cassert>
#include <cstdlib>
#include <GL/glut.h>

#include "CubeGLWidget.h"

const int HALF_RANGE = 200;
const int MAX_VELOCITY = 3;
const double GRAVITY = 3;

CubeGLWidget::CubeGLWidget(QWidget* const parent) :
	AnimatedGLWidget(parent)
{
	for(int i = 0; i < CubeGLWidget::NUM_CUBES; i++) {
		const int size = 1 + rand() % (HALF_RANGE / 7);
		Cube cube = {
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
		cubes << cube;
	}
}

void CubeGLWidget::tick(const float& elapsed)
{
	static const QVector3D VEC_X(-1, 1, 1);
	static const QVector3D VEC_Y(1, -1, 1);
	AnimatedGLWidget::tick(elapsed);
	for (QList<Cube>::iterator q = cubes.begin(); q != cubes.end(); ++q) {
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

void CubeGLWidget::render()
{
	glTranslatef(0, 0, -HALF_RANGE - 100);
	for (QList<Cube>::const_iterator cube = cubes.begin(); cube != cubes.end(); ++cube) {
		glColor3f(cube->color.redF(), cube->color.greenF(), cube->color.blueF());
		glPushMatrix();
		glTranslatef(cube->pos.x(), cube->pos.y(), cube->pos.z());
		glutSolidCube(2 * cube->size);
		glPopMatrix();
	}
}

void CubeGLWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float) width / height, 1, 800);
	glMatrixMode(GL_MODELVIEW);
}
