#include "util.h"
#include <cmath>

namespace nt
{

void setGLFrustrum(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
	GLdouble xmin, xmax, ymin, ymax;

	ymax = zNear * tan(fovy * M_PI / 360.0);
	ymin = -ymax;
	xmin = ymin * aspect;
	xmax = ymax * aspect;

	glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
}

void normalizeAngle(float &angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle > 2 * M_PI )
		angle -= 2 * M_PI;
}

}
