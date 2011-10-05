#ifndef RANDOMSTIPPLEGLWIDGET_H
#define RANDOMSTIPPLEGLWIDGET_H

#include <QList>
#include <QColor>

#include "GLWidget.h"

/**
 * Draws a series of horizontal lines on the screen. The lines vary by the
 * amount of "stippling" used on them. In this case, the lines are randomly
 * stippled, producing an interesting effect.
 */
class RandomStippleGLWidget : public GLWidget
{
	Q_OBJECT

	// The number of lines generated on construction.
	static const int NUM_LINES = 10;

	// Half the length of a line; will be rendered from -LINE_HALF_LENGTH to LINE_HALF_LENGTH
	static const int LINE_HALF_LENGTH = 80;

	QList<QColor> colors;
	QList<GLushort> stipples;

public:
	RandomStippleGLWidget();
protected:
	void render();
};

#endif // RANDOMSTIPPLEGLWIDGET_H
