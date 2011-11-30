#ifndef UTIL_H
#define UTIL_H

#include <QGLWidget>

namespace nt
{
	void setGLFrustrum(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
	void normalizeAngle(float &angle);
}

#endif // UTIL_H
