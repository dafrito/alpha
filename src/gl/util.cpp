#include "gl/util.hpp"

#include <cmath>

namespace nt {
namespace gl {

void setGLFrustum(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
	GLdouble xmin, xmax, ymin, ymax;

	xmax = zNear * tan(fovy * M_PI / 360.0);
	xmin = -xmax;
	ymin = xmin / aspect;
	ymax = xmax / aspect;

	glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
}

void glVertex(const float& x, const float& y, const float& z)
{
    glVertex3f(x, y, z);
}

void glVertex(const double& x, const double& y, const double& z)
{
    glVertex3d(x, y, z);
}

void glNormal(const float& x, const float& y, const float& z)
{
    glNormal3f(x, y, z);
}

void glNormal(const double& x, const double& y, const double& z)
{
    glNormal3d(x, y, z);
}

void glTranslate(const float& x, const float& y, const float& z)
{
    glTranslatef(x, y, z);
}

void glTranslate(const double& x, const double& y, const double& z)
{
    glTranslated(x, y, z);
}

void drawText(FTFont& font, const char* text, int yOffset)
{
	glPushMatrix();
	const float width = font.BBox(text).Upper().X();
	glTranslatef(-width/2, yOffset + 2 + font.FaceSize(), 0);
	font.Render(text);
	glPopMatrix();
}

Vector3<double> getAxisAngles(Vector3<double>& vec)
{
	Vector3<double> Rot;
	if (vec.x() == 0) {
		if (vec.y() >= 0){
			Rot.setZ( 0 );
		} else {
			Rot.setZ(M_PI_2 * 2);
		}
	} else if (vec.y() == 0) {
		if (vec.x() > 0) {
			Rot.setZ(M_PI_2 * 3);
		} else {
			Rot.setZ(M_PI_2);
		}
	} else {
		// figure out correct total angle: changes based on quadrant
		Rot.setZ( atan( vec.y() / vec.x() ) );
		if (vec.x() < 0){
			Rot.setZ(Rot.z() + M_PI_2);
		} else {
			Rot.setZ(Rot.z() + M_PI_2 * 3);
		}
	}
	// horizontal distance
	const double dxy = sqrt(
		vec.x() * vec.x() + vec.y() * vec.y()
	);
	// vertical and horizontal angle calculation's aren't exacly the same
	if (vec.z() == 0) {
		Rot.setX(0);
	} else if (dxy == 0) {
		if (vec.z() > 0){
			Rot.setX( M_PI_2);
		} else {
			Rot.setX( M_PI_2 * 3);
		}
	} else {
		Rot.setX(atan( dxy / vec.z() ));
		if (vec.z() < 0){
			Rot.setX(M_PI_2 * 3 - Rot.x());
		} else {
			Rot.setX(M_PI_2 - Rot.x());
		}
	}
	return Rot;
}

void glViewport(const Box2<int>& viewArea)
{
    ::glViewport(
        viewArea.left(),
        viewArea.top(),
        viewArea.width(),
        viewArea.height()
    );
}

void glScissor(const Box2<int>& viewArea)
{
    ::glScissor(
        viewArea.left(),
        viewArea.top(),
        viewArea.width(),
        viewArea.height()
    );
}

} // namespace gl
} // namespace nt
