#ifndef UTIL_H
#define UTIL_H

#include <QGLWidget>
#include <QVector3D>
#include <cmath>
#include <FTGL/ftgl.h>

#include "Vector3.hpp"

namespace {
const float TO_DEGREES = 180 / M_PI;
const float TO_RADIANS = M_PI / 180;
}

namespace nt {
namespace gl {

void setGLFrustum(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);

void glVertex(const QVector3D&);
void glNormal(const QVector3D&);
void drawText(FTFont& font, const char* text, int yOffset);

template <class U>
void glTranslate(const Vector3<float, U>& vec)
{
    glTranslatef(vec.x(), vec.y(), vec.z());
}

template <class U>
void glTranslate(const Vector3<double, U>& vec)
{
    glTranslated(vec.x(), vec.y(), vec.z());
}

// namespace nt

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

Vector3<double> getAxisAngles(Vector3<double>& vec);

} // namespace gl
} // namespace nt

#endif // UTIL_H
