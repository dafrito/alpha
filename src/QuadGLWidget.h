#ifndef QUADGLWIDGET_H
#define QUADGLWIDGET_H

#include <QList>
#include <QColor>
#include <QVector3D>

#include "AnimatedGLWidget.h"

struct Quad
{
	QVector3D pos;
	const QColor color;
	const unsigned int size;
	QVector3D velocity;
};

/**
 * A demonstration showing a small number of randomly sized and positioned
 * quads.
 */
class QuadGLWidget : public AnimatedGLWidget
{
	Q_OBJECT

	// The number of rendered quads
	static const int NUM_QUADS = 60;

	QList<Quad> quads;
public:
	QuadGLWidget(QWidget* const parent = 0);
protected:
	void resizeGL(int, int);
	void render();
protected slots:
	void tick(const float& elapsed);
};

#endif // QUADGLWIDGET_H
