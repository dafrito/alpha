#ifndef STARGLWIDGET_H
#define STARGLWIDGET_H

#include <QVector3D>

#include "GLWidget.h"

class StarGLWidget : public GLWidget
{
    Q_OBJECT

	bool showingInsignificantEdges;

public:
	StarGLWidget(QWidget* const parent = 0);
public slots:

	/**
	 * Whether to draw the lines in insignificant edges. There's no real magic
	 * here; edges that are insignificant are explicitly set to {@code false}
	 * with this flag.
	 */
	void showInsignificantEdges(const bool showingInsignificantEdges)
	{
		this->showingInsignificantEdges = showingInsignificantEdges;
		updateGL();
	}
protected:
	void render();
};

#endif // STARGLWIDGET_H
