#include "LuaGLWidget.h"
#include <QFile>
#include "GL/glut.h"
#include "LuaGlobal.hpp"

LuaGLWidget::LuaGLWidget() :
	timer(this)
{
	connect(&timer, SIGNAL(timeout(const float&)), this, SLOT(tick(const float&)));
	connect(&timer, SIGNAL(timeout(const float&)), this, SLOT(updateGL()));
	timer.startOnShow(this);

	QFile file("src/anim.lua");
	lua(file);
}

void LuaGLWidget::tick(const float& elapsed)
{
	lua["Tick"](&square, elapsed);
}

#include <QDebug>

void LuaGLWidget::render()
{
	glTranslatef(square.x, square.y, 0);
	glColor3f(1, 0, 0);
	glutSolidCube(40);
}
