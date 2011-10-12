#ifndef TORUSGLWIDGET_H
#define TORUSGLWIDGET_H

#include "GLWidget.h"
#include <cmath>

class TorusGLWidget : public GLWidget
{
public:
	TorusGLWidget(QWidget* parent = 0);
	~TorusGLWidget();
protected:
	void initializeGL();
	void render();
};

TorusGLWidget::TorusGLWidget(QWidget* parent) : GLWidget(parent) {}

void renderTorus();

void TorusGLWidget::initializeGL()
{
	GLWidget::initializeGL();
	setXRotation(90);

	glNewList(1, GL_COMPILE);
	renderTorus();
	glEndList();
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

void renderTorus()
{
	const int slices = 360;
	const int third = slices/3;
	const float angle = (float) 360/slices;

	for ( float i = 1; i <= slices ; i++ ) {
		glRotatef(angle,0,1,0);
		glPushMatrix();
		{
			if (i < 1*third) {
				glColor3f(1-(i/third),i/(third),0);
			}
			else if (i < 2*third) {
				glColor3f(0,1-((i-third)/third),(i-third)/third);
			}
			else {
				glColor3f((i-2*third)/third,0,1-((i-2*third)/third));
			}
			glTranslatef(50,0,0);
			Circlef(30,40);
		}
		glPopMatrix();
		
	}
}

void TorusGLWidget::render()
{
	glCallList(1);
}

TorusGLWidget::~TorusGLWidget()
{
	glDeleteLists(1, 1);
}

#endif // TORUSGLWIDGET_H
