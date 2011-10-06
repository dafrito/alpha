#ifndef CONEGLWIDGET_H
#define CONEGLWIDGET_H

#include <QVector3D>

#include "GLWidget.h"

class ConeGLWidget : public GLWidget
{
    Q_OBJECT

	bool useDepthTesting;
	bool backFaceCulling;
	bool drawBacksAsWireframe;
	bool correctWindingOrder;

	QList<QVector3D> innerCircle;
	QList<QVector3D> outerCircle;
public:
	ConeGLWidget(QWidget* const parent = 0);
public slots:
	/**
	 * Sets whether depth testing is used when rendering pixels. If {@code true},
	 * the polygon will appear correctly. If {@code false}, polygons that are
	 * drawn later in the rendering process will occlude polygons drawn earlier.
	 * In this demonstration, this means that the bottom of the cone will always
	 * occlude the cone portion.
	 */
	void setUseDepthTesting(const bool useDepthTesting)
	{
		this->useDepthTesting = useDepthTesting;
		updateGL();
	}

	bool usingDepthTesting()
	{
		return useDepthTesting;
	}

	/**
	 * Sets whether back-facing polygons are drawn. If this is {@code true} and
	 * {@link #correctWindingOrder} is {@code false}, the cone will appear
	 * incorrectly. This is intentional to demonstrate how occlusion is done.
	 */
	void setUseBackFaceCulling(const bool backFaceCulling)
	{
		this->backFaceCulling = backFaceCulling;
		updateGL();
	}

	bool usingBackFaceCulling()
	{
		return backFaceCulling;
	}

	/**
	 * Draws back-facing surfaces as a wireframe. Otherwise, they're drawn as
	 * filled surfaces. This has no effect if {@link #backFaceCulling} is
	 * {@code true}.
	 */
	void setDrawBacksAsWireframe(const bool drawBacksAsWireframe)
	{
		this->drawBacksAsWireframe = drawBacksAsWireframe;
		updateGL();
	}
	
	bool drawingBacksAsWireframes()
	{
		return drawBacksAsWireframe && (!usingBackFaceCulling() || !usingDepthTesting());
	}

	/**
	 * Corrects the winding order so that the cone can be drawn properly. If
	 * {@link #backFaceCulling} is {@code true}, this must be also be
	 * {@code true} for the cone to appear correctly.
	 */
	void setCorrectWindingOrder(const bool correctWindingOrder)
	{
		this->correctWindingOrder = correctWindingOrder;
		updateGL();
	}

	bool correctingWindingOrder()
	{
		return correctWindingOrder || !usingBackFaceCulling();
	}

protected:
	void initializeGL();
	void render();
};

#endif // CONEGLWIDGET_H
