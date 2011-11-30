#ifndef UTIL_H
#define UTIL_H

#include <QGLWidget>

namespace nt
{
	void setGLFrustrum(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);

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
