#ifndef CUBEGLWIDGET_H
#define CUBEGLWIDGET_H

#include <QList>
#include <QColor>
#include <QVector3D>

#include "AnimatedGLWidget.hpp"

// TODO Replace this with Cuboid
struct Cube
{
	QVector3D pos;
	QColor color;
	unsigned int size;
	QVector3D velocity;
};

/**
 * A demonstration showing a small number of randomly sized and positioned
 * cubes.
 */
class CubeGLWidget : public AnimatedGLWidget
{
	Q_OBJECT

	// The number of rendered cubes
	static const int NUM_CUBES = 60;

	QList<Cube> cubes;
public:
	CubeGLWidget(QWidget* const parent = 0);
protected:
	void initializeGL();
	void resizeGL(int, int);
	void render();
protected slots:
	void tick(const double& elapsed);
};

#endif // CUBEGLWIDGET_H
