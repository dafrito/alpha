#ifndef TORUSGLWIDGET_H
#define TORUSGLWIDGET_H

#include "GLWidget.h"
#include <cmath>

class TorusGLWidget : public GLWidget
{
public:
	TorusGLWidget(QWidget* parent = 0);
protected:
	void initializeGL();
	void render();
};

TorusGLWidget::TorusGLWidget(QWidget* parent) : GLWidget(parent) {}

void TorusGLWidget::initializeGL()
{
	GLWidget::initializeGL();
	setXRotation(90);
	setYRotation(0);
	setZRotation(0);
}

void Circlef (float radius,float vertices = 40) {
    glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= vertices; i++) {
		const float angle = i * 2 * (3.14159 / (float) vertices);
		glVertex2f(
			radius * (float) sin(angle),
			radius * (float) cos(angle)
		);
	}
    glEnd();
}

void TorusGLWidget::render()
{
	
	for ( int i = 0; i <= 360 ; i++ ) {
		glRotatef(i,0,1,0);
		glPushMatrix();
		{
			glTranslatef(50,0,0);
			Circlef(30,40);
		}
		glPopMatrix();
		
	}
}

#endif // TORUSGLWIDGET_H
