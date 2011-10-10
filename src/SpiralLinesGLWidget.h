#ifndef SPIRALLINESGLWIDGET_H
#define SPIRALLINESGLWIDGET_H

#include "GLWidget.h"
#include <cmath>

class SpiralLinesGLWidget : public GLWidget
{
public:
	SpiralLinesGLWidget(QWidget* parent = 0);
protected:
	void initializeGL();
	void render();
};

SpiralLinesGLWidget::SpiralLinesGLWidget(QWidget* parent) : GLWidget(parent) {}

void SpiralLinesGLWidget::initializeGL()
{
	GLWidget::initializeGL();
	setXRotation(-45);
	setYRotation(15);
	setZRotation(45);
}

void SpiralLinesGLWidget::render()
{
	// How many revolutions of the spiral are rendered.
	static const float PI = 3.14159;

	glBegin(GL_LINES); //how do you make GL_LINES not have spaces?
		//the java code C++'d
		/*for (float angle = 0; angle < PI ; angle +=  PI / 5.0f) {
			float x = 50.0f * (float) sin(angle);
			float y = 50.0f * (float) cos(angle);
			glVertex2f(x, y);

			x = 50.0f * (float) sin(PI + angle);
			y = 50.0f * (float) cos(PI + angle);
			glVertex2f(x, y);
		*/
		//An actual spiral
		for (float angle = 0; angle < PI*20 ; angle +=  PI / 200.0f) {
			float x = angle * (float) sin(angle);
			float y = angle * (float) cos(angle);
			glVertex2f(x, y);
		
		}
	
	glEnd();
}

#endif // SPIRALLINESGLWIDGET_H
