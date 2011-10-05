#include "AtomGLWidget.h"

AtomGLWidget::AtomGLWidget() :
	timer(new QTimer(this)),
	rotation(0)
{
	connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
}

void AtomGLWidget::initializeGL()
{
	GLWidget::initializeGL();
	setXRotation(-45);
	setYRotation(15);
	setZRotation(45);

	glEnable(GL_DEPTH_TEST);
}

void AtomGLWidget::showEvent(QShowEvent* const)
{
	if(!timer->isActive()) {
		timer->start(1000 / 60);
	}
}

void AtomGLWidget::tick()
{
	rotation += 5.0f;
	while (rotation > 360) {
		rotation -= 360;
	}
	updateGL();
}

void AtomGLWidget::render()
{
	glClear(GL_DEPTH_BUFFER_BIT);

	glTranslatef(0, 0, -15);
	glColor3f(1, 0, 0);
	glutSolidSphere(10, 15, 15);

	glColor3f(1, 1, 0);

	glPushMatrix();
	glRotatef(rotation, 0, 1, 0);
	glTranslatef(90, 0, 0);
	glutSolidSphere(6, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 0, 1);
	glRotatef(rotation, 0, 1, 0);
	glTranslatef(-70, 0, 0);
	glutSolidSphere(6, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 0, 0, 1);
	glRotatef(rotation, 0, 1, 0);
	glTranslatef(0, 0, 60);
	glutSolidSphere(6, 15, 15);
	glPopMatrix();
}

void AtomGLWidget::hideEvent(QHideEvent* const)
{
	if(timer->isActive()) {
		timer->stop();
	}
}

