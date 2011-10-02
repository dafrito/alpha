#include <QtGui>
#include <QtOpenGL>

#include <math.h>

#include "GLDemo.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif


// We scale rotation such that 1 unit of xRot, yRot, or zRot is
// equal to 1/ROTATION_SCALE degrees. Therefore, when you want to
// set rotation, you need to multiply by this scale to get expected
// results:
//
// xRot = 45 * ROTATION_SCALE; // xRot is now 45 degrees
const int ROTATION_SCALE = 16;

GLDemo::GLDemo(QWidget *parent)
	: QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
	xRot = 0;
	yRot = 0;
	zRot = 0;
}

void GLDemo::initializeGL()
{
	qglClearColor(Qt::black);
	glEnable(GL_MULTISAMPLE);
}

void GLDemo::paintGL()
{
	static const float ROTATION_DENOM = 1 / (float)ROTATION_SCALE;

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -10.0);
	glRotatef((float)(xRot) * ROTATION_DENOM, 1.0, 0.0, 0.0);
	glRotatef((float)(yRot) * ROTATION_DENOM, 0.0, 1.0, 0.0);
	glRotatef((float)(zRot) * ROTATION_DENOM, 0.0, 0.0, 1.0);

	this->render();
}

void GLDemo::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);

	const float aspectRatio = (float) height / (float) width;
	const float range = 100.0;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width <= height) {
		glOrtho(-range, range, -range * aspectRatio, range * aspectRatio, 2 * range, 2 * -range);
	} else {
		glOrtho(-range / aspectRatio, range / aspectRatio, -range, range, 2 * range, 2 * -range);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/**
 * Listen for the escape key for quick exiting.
 */
void GLDemo::keyPressEvent(QKeyEvent *e)
{
	if (e->key() == Qt::Key_Escape)
		close();
	else
		QWidget::keyPressEvent(e);
}

void GLDemo::mousePressEvent(QMouseEvent *event)
{
	lastPos = event->pos();
}

static void qNormalizeAngle(int &angle)
{
	while (angle < 0)
		angle += 360 * ROTATION_SCALE;
	while (angle > 360 * ROTATION_SCALE)
		angle -= 360 * ROTATION_SCALE;
}

/**
 * Interpret the mouse event to rotate the camera around the scene.
 */
void GLDemo::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		setXRotation(xRot + dy * ROTATION_SCALE / 2);
		setYRotation(yRot + dx * ROTATION_SCALE / 2);
	} else if (event->buttons() & Qt::RightButton) {
		setXRotation(xRot + dy * ROTATION_SCALE / 2);
		setZRotation(yRot + dx * ROTATION_SCALE / 2);
	}
	lastPos = event->pos();
}

void GLDemo::setXRotation(int angle)
{
	angle *= ROTATION_SCALE;
	qNormalizeAngle(angle);
	if (angle != xRot) {
		xRot = angle;
		updateGL();
	}
}

void GLDemo::setYRotation(int angle)
{
	angle *= ROTATION_SCALE;
	qNormalizeAngle(angle);
	if (angle != yRot) {
		yRot = angle;
		updateGL();
	}
}

void GLDemo::setZRotation(int angle)
{
	angle *= ROTATION_SCALE;
	qNormalizeAngle(angle);
	if (angle != zRot) {
		zRot = angle;
		updateGL();
	}
}
