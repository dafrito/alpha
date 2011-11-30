#include "Camera.h"
#include "util.h"
#include <cassert>

using namespace nt;

Camera::Camera(Player* t) :
	moveWithTarget(true),
	rotateWithTarget(true),
	rotateTarget(false),
	zoomSpeed(5),
	zSpeed(0.009),
	xSpeed(0.007),
	target(t),
	targetDistance(100),
	maxDistance(800)
{
	setXRotation(0);
	setYRotation(0);
	setZRotation(0);
	setTarget(target);

}

void Camera::setTarget(Player* mob)
{
	assert(target != 0);
	mob->alpha = target->alpha;
	target->alpha = target->defaultAlpha;
	target = mob;
	alignWithTarget();
}
// target rotates to face away from camera
void Camera::alignTarget()
{
		target->xRot = getXRotation();
		target->yRot = getYRotation();
		target->zRot = getZRotation();
}
// camera rotates to face at back of target
void Camera::alignWithTarget()
{
	setXRotation(target->xRot);
	setYRotation(target->yRot);
	setZRotation(target->zRot);

}

void Camera::setTargetDistance(float distance)
{
	if (distance < 0) { distance = 0;}
	if (distance > maxDistance) {distance = maxDistance;}
	targetDistance = distance;
	target->alpha = targetDistance / 100;
}

void Camera::applySettings() const
{
	float toDegrees = 180 / M_PI;
	// distance the camera from the target
	glTranslatef( 0.0f,0.0f, -targetDistance);
	glRotatef(-xRot * toDegrees, 1.0, 0.0, 0.0);
	glRotatef(-yRot * toDegrees, 0.0, 1.0, 0.0);
	glRotatef(-zRot * toDegrees, 0.0, 0.0, 1.0);
	// keeps the target in the center of the screen
	glTranslatef( -target->pos.x(), -target->pos.y(), -target->pos.z() );
}

void Camera::setXRotation(float angle)
{
	angle += M_PI_2;
	normalizeAngle(angle);
	// keep us from flipping upside down
	if ( angle > 3 * M_PI_2 ) { angle = 2 * M_PI; }
	else if ( angle > M_PI ) {angle = M_PI;}
	xRot = angle;
}

void Camera::setYRotation(float angle)
{
	normalizeAngle(angle);
	yRot = angle;
}

void Camera::setZRotation(float angle)
{
	normalizeAngle(angle);
	zRot = angle;
}
