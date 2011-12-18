#include "ntgl.h"
#include <cmath>

namespace nt
{

void setGLFrustum(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
	GLdouble xmin, xmax, ymin, ymax;

	xmax = zNear * tan(fovy * M_PI / 360.0);
	xmin = -xmax;
	ymin = xmin / aspect;
	ymax = xmax / aspect;

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
