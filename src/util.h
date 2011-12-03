#ifndef UTIL_H
#define UTIL_H

#include <QGLWidget>
#include <QVector3D>
#include <cmath>

namespace nt
{
	const float TO_DEGREES = 180 / M_PI;
	const float TO_RADIANS = M_PI / 180;

	void setGLFrustrum(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);

	void glVertex(const QVector3D&);
	void glNormal(const QVector3D&);

	template <typename T>
	void normalizeAngle(T& angle)
	{
		while (angle < 0)
			angle += 2 * M_PI;
		while (angle > 2 * M_PI )
			angle -= 2 * M_PI;
	}
}

#endif // UTIL_H
