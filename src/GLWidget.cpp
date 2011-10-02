#include <QtGui>
#include <QtOpenGL>

#include <math.h>

#include "GLWidget.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

GLWidget::GLWidget(QWidget *parent)
	: QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
	xRot = 0;
	yRot = 0;
	zRot = 0;
}

void GLWidget::initializeGL()
{
	qglClearColor(Qt::black);
	glEnable(GL_MULTISAMPLE);
}

void GLWidget::paintGL()
{
	static const float ROTATION_DENOM = 1 / (float)GLWidget::ROTATION_SCALE;

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -10.0);
	glRotatef((float)(xRot) * ROTATION_DENOM, 1.0, 0.0, 0.0);
	glRotatef((float)(yRot) * ROTATION_DENOM, 0.0, 1.0, 0.0);
	glRotatef((float)(zRot) * ROTATION_DENOM, 0.0, 0.0, 1.0);

	this->render();
}

void GLWidget::resizeGL(int width, int height)
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
void GLWidget::keyPressEvent(QKeyEvent *e)
{
	if (e->key() == Qt::Key_Escape)
		close();
	else
		QWidget::keyPressEvent(e);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
	lastPos = event->pos();
}

/**
 * Interpret the mouse event to rotate the camera around the scene.
 */
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		setScaledXRotation(xRot + dy * GLWidget::ROTATION_SCALE / 2);
		setScaledYRotation(yRot + dx * GLWidget::ROTATION_SCALE / 2);
	} else if (event->buttons() & Qt::RightButton) {
		setScaledXRotation(xRot + dy * GLWidget::ROTATION_SCALE / 2);
		setScaledZRotation(zRot + dx * GLWidget::ROTATION_SCALE / 2);
	}
	lastPos = event->pos();
}

void GLWidget::setScaledXRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != xRot) {
		xRot = angle;
		emit xRotationChanged(angle);
		updateGL();
	}
}

void GLWidget::setScaledYRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != yRot) {
		yRot = angle;
		emit yRotationChanged(angle);
		updateGL();
	}
}

void GLWidget::setScaledZRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != zRot) {
		zRot = angle;
		emit zRotationChanged(angle);
		updateGL();
	}
}
