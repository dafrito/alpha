#ifndef ATOMGLWIDGET_H
#define ATOMGLWIDGET_H

#include "GLWidget.h"

#include <cmath>
#include <QHideEvent>
#include <QShowEvent>
#include <QTimer>
#include <GL/glut.h>

class AtomGLWidget : public GLWidget
{
	Q_OBJECT

public:
	AtomGLWidget();
protected:
	void showEvent(QShowEvent* event);
	void hideEvent(QHideEvent* event);

	void initializeGL();
	void render();
private slots:
	void tick();
private:
	QTimer* timer;
	float rotation;
};

#endif // ATOMGLWIDGET_H
