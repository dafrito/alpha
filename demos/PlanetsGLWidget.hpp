#ifndef PLANETSGLWIDGET_H
#define PLANETSGLWIDGET_H

#include "GLWidget.hpp"

#include <cmath>
#include <QHideEvent>
#include <QShowEvent>
#include <QTimer>
#include <GL/glut.h>
#include "AnimatedGLWidget.hpp"
#include <FTGL/ftgl.h>

class PlanetsGLWidget : public AnimatedGLWidget
{
	Q_OBJECT

	FTPolygonFont font;
public:
	PlanetsGLWidget(QWidget* const parent = 0);
protected:
	void initializeGL();
	void render();
	void tick(const float& elapsed);
private:
	float rotation;
};

#endif // PLANETSGLWIDGET_H
