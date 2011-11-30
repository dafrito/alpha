#include "Camera.h"
#include "util.h"

using namespace nt;

Camera::Camera() :
	moveWithTarget(true),
	rotateWithTarget(true),
	rotateTarget(false),
	zoomSpeed(5),
	zSpeed(0.009),
	xSpeed(0.007),
	targetDistance(100),
	maxDistance(800)
{}

void Camera::setTarget(Player* mob)
{
	//target->alpha = target->defaultAlpha;
	target = mob;
	// camera faces what the target faces
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

	if (angle != xRot) {
		xRot = angle;
	}
}

void Camera::setYRotation(float angle)
{
	normalizeAngle(angle);
	if (angle != yRot) {
		yRot = angle;
	}
}

void Camera::setZRotation(float angle)
{
	normalizeAngle(angle);
	if (angle != zRot) {
		zRot = angle;

	}
}
