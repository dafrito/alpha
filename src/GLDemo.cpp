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
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -10.0);
	glRotatef(xRot / ROTATION_SCALE, 1.0, 0.0, 0.0);
	glRotatef(yRot / ROTATION_SCALE, 0.0, 1.0, 0.0);
	glRotatef(zRot / ROTATION_SCALE, 0.0, 0.0, 1.0);

	this->render();
}

void GLDemo::resizeGL(int width, int height)
{
	int side = qMin(width, height);
	glViewport((width - side) / 2, (height - side) / 2, side, side);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
#ifdef QT_OPENGL_ES_1
	glOrthof(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#else
	glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#endif
	glMatrixMode(GL_MODELVIEW);
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

/**
 * Interpret the mouse event to rotate the camera around the scene.
 */
void GLDemo::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		setXRotation(xRot/ROTATION_SCALE + dx);
		setYRotation(yRot/ROTATION_SCALE + dy);
	} else if (event->buttons() & Qt::RightButton) {
		setXRotation(xRot/ROTATION_SCALE + dx);
		setZRotation(zRot/ROTATION_SCALE + dy);
	}
	lastPos = event->pos();
}

static void qNormalizeAngle(int &angle)
{
	while (angle < 0)
		angle += 360 * ROTATION_SCALE;
	while (angle > 360 * ROTATION_SCALE)
		angle -= 360 * ROTATION_SCALE;
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
