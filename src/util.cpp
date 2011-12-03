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

void glVertex(const QVector3D& vec)
{
	glVertex3d(vec.x(), vec.y(), vec.z());
}

void glNormal(const QVector3D& vec)
{
	glNormal3d(vec.x(), vec.y(), vec.z());
}

}
