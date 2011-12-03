#include "LuaGLWidget.h"
#include <QFile>
#include <QVector3D>
#include "util.h"
#include "LuaGlobal.hpp"

#include <cmath>

static float func(const float& x, const float& z)
{
	return cos(x) * log(z);
}

LuaGLWidget::LuaGLWidget(QWidget* const parent) :
	GLWidget(parent),
	timer(this, 1000 / 60)
{
	connect(&timer, SIGNAL(timeout(const float&)), this, SLOT(tick(const float&)));
	connect(&timer, SIGNAL(timeout(const float&)), this, SLOT(updateGL()));
	timer.startOnShow(this);
	update(func);
}

void LuaGLWidget::initializeGL()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	sceneList = glGenLists(1);
	glNewList(sceneList, GL_COMPILE);
	renderScene();
	glEndList();
}

void LuaGLWidget::tick(const float&)
{
}

void LuaGLWidget::renderScene()
{
	glTranslatef(0, -HALFSIZE/8, 0);
	glRotatef(-150, 0, 1, 0);
	glRotatef(-10, 1, 0, 0);
	glBegin(GL_QUADS);
	for (int y = -HALFSIZE; y < HALFSIZE-1; y++) {
		for (int x = -HALFSIZE; x < HALFSIZE-1; x++) {
			// XXX This code is recklessly inefficient; we either don't need
			// QVector3D's or we should reuse objects outside of this loop.
			QVector3D a(x, AMPLITUDE*get(x, y), y);
			QVector3D b(x, AMPLITUDE*get(x, y+1), y+1);
			QVector3D c(x+1, AMPLITUDE*get(x+1, y+1), y+1);
			QVector3D d(x+1, AMPLITUDE*get(x+1, y), y);
			QVector3D norm = normal(x,y);
			// FIXME These normals produce visible edges; I think the average
			// is generated incorrectly.
			QVector3D rnorm = average(norm, normal(x, y+1));
			QVector3D tnorm = average(norm, normal(x+1, y));
			QVector3D lnorm = average(norm, normal(x, y-1));
			QVector3D bnorm = average(norm, normal(x-1, y));
			renderNormal(average(rnorm, bnorm));
			renderVertex(b);
			renderNormal(average(rnorm, tnorm));
			renderVertex(c);
			renderNormal(average(lnorm, tnorm));
			renderVertex(d);
			renderNormal(average(lnorm, bnorm));
			renderVertex(a);
		}
	}
	glEnd();
}

void LuaGLWidget::render()
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glCallList(sceneList);
}

void LuaGLWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	nt::setGLFrustrum(60, (float) width / height, 1, 800);
	glMatrixMode(GL_MODELVIEW);
}

LuaGLWidget::~LuaGLWidget()
{
	glDeleteLists(sceneList, 1);
}
