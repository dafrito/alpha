#ifndef UTIL_H
#define UTIL_H

#include <QGLWidget>
#include <QVector3D>
#include <cmath>
#include <FTGL/ftgl.h>

namespace nt
{
	const float TO_DEGREES = 180 / M_PI;
	const float TO_RADIANS = M_PI / 180;

	void setGLFrustum(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);

	void glVertex(const QVector3D&);
	void glNormal(const QVector3D&);
	void drawText(FTFont& font, const char* text, int yOffset);

	template <typename T>
	void normalizeRadians(T& angle)
	{
		while (angle < 0)
			angle += 2 * M_PI;
		while (angle >= 2 * M_PI)
			angle -= 2 * M_PI;
	}

	template <typename T>
	void normalizeDegrees(T& angle)
	{
		while (angle < 0)
			angle += 360;
		while (angle >= 360)
			angle -= 360;
	}

} // namespace nt

#endif // UTIL_H
