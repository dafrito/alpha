#ifndef UTIL_H
#define UTIL_H

#include <GL/gl.h>
#include <cmath>
#include <FTGL/ftgl.h>

#include "Vector3.hpp"
#include "Box2.hpp"
#include "Physical.hpp"

namespace {
const float TO_DEGREES = 180 / M_PI;
const float TO_RADIANS = M_PI / 180;
}

namespace nt {
namespace gl {

void setGLFrustum(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);

void drawText(FTFont& font, const char* text, int yOffset);

template <typename Vector>
void glVertex(const Vector& vec);
void glVertex(const float& x, const float& y, const float& z);
void glVertex(const double& x, const double& y, const double& z);

template <typename Vector>
void glNormal(const Vector& vec);
void glNormal(const float& x, const float& y, const float& z);
void glNormal(const double& x, const double& y, const double& z);

template <typename Vector>
void glTranslate(const Vector& vec);
void glTranslate(const float& x, const float& y, const float& z);
void glTranslate(const double& x, const double& y, const double& z);

template <typename Scalar>
void glTransform(const Physical<Scalar>& physical);

template <typename Scalar>
void glReverseTransform(const Physical<Scalar>& physical);

void glScissor(const Box2<int>& screenArea);

Vector3<double> getAxisAngles(Vector3<double>& vec);

void glViewport(const Box2<int>& viewArea);

// Implementation follows:

template <typename Vector>
void glVertex(const Vector& vec)
{
	glVertex(vec.x(), vec.y(), vec.z());
}

template <typename Vector>
void glNormal(const Vector& vec)
{
	glNormal(vec.x(), vec.y(), vec.z());
}

template <typename Vector>
void glTranslate(const Vector& vec)
{
    glTranslate(vec.x(), vec.y(), vec.z());
}

template <class T, class U>
void glRotateRadians(const Vector3<T, U>& vec)
{
    glRotated(vec.z() * TO_DEGREES, 0, 0, 1);
    glRotated(vec.x() * TO_DEGREES, 1, 0, 0);
    //glRotated(vec.y() * TO_DEGREES, 0, 1, 0);

}

template <class T, class U>
void glRotateDegrees(const Vector3<T, U>& vec)
{
    glRotated(vec.z(), 0, 0, 1);
    glRotated(vec.x(), 1, 0, 0);
    // glRotated(vec.y(), 0, 1, 0);

}

template <class U>
void glRotateRadians(const Vector3<float, U>& vec)
{
    glRotatef(vec.z() * TO_DEGREES, 0, 0, 1);
    glRotatef(vec.x() * TO_DEGREES, 1, 0, 0);
    //glRotatef(vec.y() * TO_DEGREES, 0, 1, 0);

}

template <class U>
void glRotateDegrees(const Vector3<float, U>& vec)
{
    glRotatef(vec.z(), 0, 0, 1);
    glRotatef(vec.x(), 1, 0, 0);
    // glRotatef(vec.y(), 0, 1, 0);

}
// these 2 functions are for the camera
// backwards means everything flipped!
// values are negative and x is rotated before z
template <class U>
void glRotateRadiansBackwards(const Vector3<float, U>& vec)
{
    glRotatef(-vec.x() * TO_DEGREES, 1, 0, 0);
    glRotatef(-vec.z() * TO_DEGREES, 0, 0, 1);
}
template <class T, class U>
void glRotateRadiansBackwards(const Vector3<T, U>& vec)
{
    glRotated(-vec.x() * TO_DEGREES, 1, 0, 0);
    glRotated(-vec.z() * TO_DEGREES, 0, 0, 1);
}

template <typename Scalar>
void glTransform(const Physical<Scalar>& physical)
{
    glTranslate(physical.getPosition());
    glRotateRadians(physical.getRotation());
}

template <typename Scalar>
void glReverseTransform(const Physical<Scalar>& physical)
{
    glRotateRadians(physical.getRotation());
    glTranslate(-physical.getPosition());
}

} // namespace gl
} // namespace nt

#endif // UTIL_H
