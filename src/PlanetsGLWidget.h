#ifndef PLANETSGLWIDGET_H
#define PLANETSGLWIDGET_H

#include "GLWidget.h"

#include <cmath>
#include <QHideEvent>
#include <QShowEvent>
#include <QTimer>
#include <GL/glut.h>

class PlanetsGLWidget : public GLWidget
{
	Q_OBJECT

public:
	PlanetsGLWidget();
protected:
	void showEvent(QShowEvent* const);
	void hideEvent(QHideEvent* const);

	void initializeGL();
	void render();
private slots:
	void tick();
private:
	QTimer* const timer;
	float rotation;
};

#endif // PLANETSGLWIDGET_H
