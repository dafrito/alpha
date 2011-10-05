#include <cassert>
#include <cstdlib>

#include "RandomStippleGLWidget.h"


RandomStippleGLWidget::RandomStippleGLWidget(QWidget* const parent) :
	GLWidget(parent)
{
	for(int i = 0; i < RandomStippleGLWidget::NUM_LINES; i++) {
		stipples << (GLushort)rand();
		for (int j = 0; j < 2; j++) {
			colors << QColor(
				rand() % 255,
				rand() % 255,
				rand() % 255);
		}
	}
}

void RandomStippleGLWidget::render()
{

	QList<GLushort>::const_iterator stippleIter = stipples.begin();
	QList<QColor>::const_iterator colorIter = colors.begin();
	float y = -90.0f;

	glEnable(GL_LINE_STIPPLE);
	glLineWidth(2);
	glBegin(GL_LINES);
	while (stippleIter != stipples.end() && colorIter != colors.end()) {
		glLineStipple(5, *stippleIter++);
		for(int sign=-1; sign <= 1; sign += 2) {
			QColor color = *colorIter++;
			glColor3f(color.redF(), color.greenF(), color.blueF());
			glVertex2f(sign * LINE_HALF_LENGTH, y);
		}
		y += 20.0f;
	}
	glEnd();
	assert(stippleIter == stipples.end());
	assert(colorIter == colors.end());
}
