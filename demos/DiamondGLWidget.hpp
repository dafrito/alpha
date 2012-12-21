#ifndef DIAMONDGLWIDGET_H
#define DIAMONDGLWIDGET_H

#include <QVector3D>

#include "GLWidget.hpp"

class DiamondGLWidget : public GLWidget
{
    Q_OBJECT

	bool useDepthTesting;
	bool backFaceCulling;
	bool drawBacksAsWireframe;
	bool correctWindingOrder;

	QList<QVector3D> innerCircle;
	QList<QVector3D> outerCircle;
public:
	DiamondGLWidget(QWidget* const parent = 0);
public slots:
	/**
	 * Sets whether depth testing is used when rendering pixels. If {@code true},
	 * the polygon will appear correctly. If false, polygons that are
	 * drawn later in the rendering process will occlude polygons drawn earlier.
	 * In this demonstration, this means that the top of the diamond will occlude
	 * the bottom portion.
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
	 * Sets whether back-facing polygons are drawn. If the winding order is not
	 * corrected, the top of the diamond will appear incorrectly.
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
	 * filled surfaces. This has no effect if back-face culling is enabled.
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
	 * Corrects the winding order so that the top of the diamond is
	 * rendered properly if back-face culling is enabled.
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

#endif // DIAMONDGLWIDGET_H
