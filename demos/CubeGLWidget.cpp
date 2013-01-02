#include <cassert>
#include <cstdlib>
#include <GL/glut.h>
#include "gl/util.hpp"

#include "CubeGLWidget.hpp"

const int HALF_RANGE = 200;
const int MAX_VELOCITY = 3;
const double GRAVITY = 3;

CubeGLWidget::CubeGLWidget(QWidget* const parent) :
	AnimatedGLWidget(parent)
{
	for(int i = 0; i < CubeGLWidget::NUM_CUBES; i++) {
		const unsigned int size = 1 + rand() % (HALF_RANGE / 7);
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
				-MAX_VELOCITY + rand() % (MAX_VELOCITY * 2))
		};
		cubes << cube;
	}
}

void CubeGLWidget::tick(const double& elapsed)
{
	static const QVector3D VEC_X(-1, 1, 1);
	static const QVector3D VEC_Y(1, -1, 1);
	static const QVector3D VEC_Z(1, 1, -1);
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
		{
			double z = q->pos.z() + q->velocity.z();
			const double diff = abs(z) - range;
			if (diff > 0) {
				q->velocity *= VEC_Z;
				if (z > 0) {
					// Z is positive; head negative
					z = range - diff;
				} else {
					// Z is negative; head positive
					z = -range + diff;
				}
			}
			q->pos.setZ(z);
		}
		q->velocity.setY(q->velocity.y() - GRAVITY * elapsed);
	}
}

void CubeGLWidget::initializeGL()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void CubeGLWidget::render()
{
	glClear(GL_DEPTH_BUFFER_BIT);
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
	nt::gl::setGLFrustum(60, (float) width / height, 1, 800);
	glMatrixMode(GL_MODELVIEW);
}
