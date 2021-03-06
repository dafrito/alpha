#include "LogoGLWidget.hpp"

#include <QtGui>
#include <QtOpenGL>
#include <cmath>

#include "Logo.hpp"

LogoGLWidget::LogoGLWidget(QWidget* const parent) :
	GLWidget(parent),
	logo(0),
	qtGreen(QColor::fromCmykF(0.40, 0.0, 1.0, 0.0).dark()),
	qtOrange(QColor::fromCmykF(0.0, 0.45, 1.0, 0.0).dark())
{
}

void LogoGLWidget::initializeGL()
{
    qglClearColor(qtOrange);

    setXRotation(15);
    setYRotation(345);

    if (logo) {
        delete logo;
    }
    logo = new Logo(this);
    logo->setColor(qtGreen);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_MULTISAMPLE);
    static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void LogoGLWidget::render()
{
    glClear(GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -10);
    applyRotation();
    logo->draw();
}

void LogoGLWidget::resizeGL(int width, int height)
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

LogoGLWidget::~LogoGLWidget()
{
	if (logo) {
		delete logo;
		logo = 0;
	}
}
