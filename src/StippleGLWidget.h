#ifndef STIPPLEGLWIDGET_H
#define STIPPLEGLWIDGET_H

#include "GLWidget.h"
#include <cmath>

class StippleGLWidget : public GLWidget
{
public:
	StippleGLWidget(QWidget* parent = 0);
protected:
	void render();
};

StippleGLWidget::StippleGLWidget(QWidget* parent) : GLWidget(parent) {}

void StippleGLWidget::render()
{
	glEnable(GL_LINE_STIPPLE);
	int height = 160;
	int length = 100;
	int lineSpacing = 10;

	int pattern = 0xffff; //bit pattern determines which parts of the line to draw
	int factor = 3; //how many times to use each bit in the pattern before going to the next


	for (int y = -(height/2); y < (height/2); y += lineSpacing) {
		glLineStipple(factor, pattern);
		glBegin(GL_LINES);
		float percentComplete = (float) (y +(height/2)) / height;
		glColor3f(.3f + percentComplete / 3.0f, 1.0f - percentComplete, percentComplete);
		glVertex2f(-(length/2) , y );
		glVertex2f( (length/2), y  );
		glEnd();
		factor += 0;
		pattern -= 0x1111;
	}
}

#endif // STIPPLEGLWIDGET_H
