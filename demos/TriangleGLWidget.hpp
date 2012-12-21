#ifndef TRIANGLEGLWIDGET_H
#define TRIANGLEGLWIDGET_H

#include "GLWidget.hpp"

/**
 * Draws two triangles on the screen. These triangles are "front-facing", which
 * isn't relevant here but will be relevant in the future. The facing of the
 * triangles is determined by the order of vertices. This combination of
 * ordering and facing determination is called <em>winding</em>. Clockwise
 * vertices are, by OpenGL convention, facing <em>away</em> from the viewer.
 * Counter-clockwise vertices, on the other hand, are facing outward towards the
 * viewer.
 * <p>
 * The order of vertices should be consistent in a scene, and unless you're
 * doing something weird, they should be ordered such that outward faces are
 * ordered counter-clockwise.
 * <p>
 * To reverse the facing behavior of OpenGL, use {@code glFrontFace(int)}.
 * 
 */
class TriangleGLWidget : public GLWidget
{
public:
	TriangleGLWidget(QWidget* const parent = 0);
protected:
	void render();
};

TriangleGLWidget::TriangleGLWidget(QWidget* const parent) : GLWidget(parent) {}

void TriangleGLWidget::render()
{
	glTranslatef(-50, 0, 0);

	glBegin(GL_TRIANGLES);
	{
		glColor3f(1, 1, 1);
		glVertex2f(0, 0);
		glVertex2f(25, 25);
		glVertex2f(50, 0);
	}
	glEnd();

	glTranslatef(50, 0, 0);

	glBegin(GL_TRIANGLES);
	{
		glColor3f(1, 0, 0);
		glVertex2f(0, 0);

		glColor3f(0, 1, 0);
		glVertex2f(25, 25);

		glColor3f(0, 0, 1);
		glVertex2f(50, 0);
	}
	glEnd();
}

#endif // TRIANGLEGLWIDGET_H
