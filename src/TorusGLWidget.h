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
	
	for ( float i = 0; i <= 360 ; i++ ) {
		glRotatef(1,0,1,0);
		glPushMatrix();
		{
			if (i <= 120) {
				glColor3f(1-(i/120),(i/120),0);
			}
			else if (i <= 240) {
				glColor3f(0,1-(i/240),(i/240));
			}
			else {
				glColor3f(i/360,0,1-(i/360));
			}
			glTranslatef(50,0,0);
			Circlef(30,40);
		}
		glPopMatrix();
		
	}
}

#endif // TORUSGLWIDGET_H
