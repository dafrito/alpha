#include <QtGui>
#include <QtOpenGL>
#include <FTGL/ftgl.h>

#include "FontGLWidget.h"
#include "ntgl.h"

FontGLWidget::FontGLWidget(QWidget* const parent) :
	AnimatedGLWidget(parent),
	rotation(0)
{
}

void FontGLWidget::initializeGL()
{
	qglClearColor(Qt::black);
}

void FontGLWidget::tick(const float& elapsed)
{
	rotation += ROTATION_SPEED * elapsed;
	while (rotation > 360)
		rotation -= 360;
}

void FontGLWidget::render()
{
	FTOutlineFont font("../media/DejaVuSansMono.ttf");
	font.FaceSize(FONT_SIZE);
	glTranslatef(0, -5 * FONT_SIZE, 0);
	for (int i = 0; i < 10; i++) {
		float color = .3 + ((float)i/10) * .7;
		glColor3f(color, color, 1);
		glRotatef(rotation,0, 1, 0);
		font.Render("No time.");
		glTranslatef(0, FONT_SIZE, 0);
	}
}
