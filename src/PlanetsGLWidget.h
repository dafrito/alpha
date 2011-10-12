#ifndef PLANETSGLWIDGET_H
#define PLANETSGLWIDGET_H

#include "GLWidget.h"

#include <cmath>
#include <QHideEvent>
#include <QShowEvent>
#include <QTimer>
#include <GL/glut.h>
#include "AnimatedGLWidget.h"

class PlanetsGLWidget : public AnimatedGLWidget
{
	Q_OBJECT

public:
	PlanetsGLWidget(QWidget* const parent = 0);
protected:
	void initializeGL();
	void render();
protected slots:
	void tick();
private:
	float rotation;
};

#endif // PLANETSGLWIDGET_H
