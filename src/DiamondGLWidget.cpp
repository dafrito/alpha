#include <QtGui>
#include <QtOpenGL>

#include <cmath>

#include "DiamondGLWidget.h"

typedef QList<QVector3D>::const_iterator PointIter;

const float TAIL_Z = -75;

const float INNER_CIRCLE_Z = 20;
const float INNER_CIRCLE_SIZE = 35;

const float OUTER_CIRCLE_Z = 0;
const float OUTER_CIRCLE_SIZE = 50;


static const QList<QVector3D> buildCircle(const float size, const float z, const bool twisted = false)
{
	QList<QVector3D> points;
	static const float PI = 3.14159;
	float offset = 0;
	if (twisted) {
		offset = PI / 16.0f;
	}
	for (int i = 0; i <= 16; i++) {
		float angle = offset + (i * (float) PI / 8.0f);
		float x = size * (float) sin(angle);
		float y = size * (float) cos(angle);

		points << QVector3D(x, y, z);
	}

	return points;
}

DiamondGLWidget::DiamondGLWidget(QWidget* const parent) :
	GLWidget(parent),
	useDepthTesting(true),
	backFaceCulling(true),
	drawBacksAsWireframe(true),
	correctWindingOrder(true)
{
	outerCircle.append(buildCircle(OUTER_CIRCLE_SIZE, OUTER_CIRCLE_Z));
	innerCircle.append(buildCircle(INNER_CIRCLE_SIZE, INNER_CIRCLE_Z, true));
}

void DiamondGLWidget::initializeGL()
{
	glShadeModel(GL_FLAT);

	setXRotation(-50);
	setYRotation(20);
}

void DiamondGLWidget::render()
{
	const static QColor lightColor(135, 206, 250);
	const static QColor darkColor(0, 191, 255);

	glClear(GL_DEPTH_BUFFER_BIT);

	glFrontFace(GL_CCW);

	if (usingDepthTesting()) {
		glEnable(GL_DEPTH_TEST);
	} else {
		glDisable(GL_DEPTH_TEST);
	}

	if (usingBackFaceCulling()) {
		glEnable(GL_CULL_FACE);
	} else {
		glDisable(GL_CULL_FACE);
		if (drawingBacksAsWireframes()) {
			glPolygonMode(GL_BACK, GL_LINE);
		} else {
			glPolygonMode(GL_BACK, GL_FILL);
		}
	}

	int evenOrOdd = 0;

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, TAIL_Z);
	for (PointIter iter = outerCircle.begin(); iter != outerCircle.end(); ++iter) {
		const QColor* color = &lightColor;
		if (evenOrOdd++ % 2 == 0) {
			color = &darkColor;
		}
		glColor3f(color->redF(), color->greenF(), color->blueF());
		const QVector3D point = *iter;
		glVertex3d(point.x(), point.y(), point.z());
	}
	glEnd();

	{
		glBegin(GL_TRIANGLE_STRIP);
		PointIter innerIter = innerCircle.begin();
		PointIter outerIter = outerCircle.begin();
		while(innerIter != innerCircle.end() && outerIter != outerCircle.end()) {
			QVector3D point = *outerIter++;
			glColor3f(darkColor.redF(), darkColor.greenF(), darkColor.blueF());
			glVertex3d(point.x(), point.y(), point.z());
			point = *innerIter++;
			glColor3f(lightColor.redF(), lightColor.greenF(), lightColor.blueF());
			glVertex3d(point.x(), point.y(), point.z());
		}
		glEnd();
	}

	if (correctingWindingOrder()) {
		glFrontFace(GL_CW);
	}

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, INNER_CIRCLE_Z);
	for (PointIter iter = innerCircle.begin(); iter != innerCircle.end(); ++iter) {
		const QColor* color = &lightColor;
		if (evenOrOdd++ % 2 == 0) {
			color = &darkColor;
		}
		glColor3f(color->redF(), color->greenF(), color->blueF());
		const QVector3D point = *iter;
		glVertex3d(point.x(), point.y(), point.z());
	}
	glEnd();
}
