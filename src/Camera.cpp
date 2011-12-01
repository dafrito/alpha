#include "Camera.h"
#include "util.h"
#include <cassert>

using namespace nt;

Camera::Camera(Player* t) :
	target(t),
	zoomSpeed(5),
	zSpeed(0.009),
	xSpeed(0.007),
	moveWithTarget(true),
	rotateWithTarget(true),
	rotateTarget(false),
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
	// camera and object xRots are off by 1/4 turn
	target->setXRotation( getXRotation() - M_PI_2 );
	target->setYRotation( getYRotation() );
	target->setZRotation( getZRotation() );
}

// camera rotates to face at back of target
void Camera::alignWithTarget()
{
	// camera and object xRots are off by 1/4 turn
	setXRotation( target->getXRotation() + M_PI_2);
	setYRotation( target->getYRotation() );
	setZRotation( target->getZRotation() );

}

void Camera::addTargetXRotation(float x)
{

	target->addXRotation(x);
	if (rotateWithTarget)
	{
		setXRotation(xRot + x);
	}
}
void Camera::addTargetYRotation(float y)
{
	target->addYRotation(y);
	if (rotateWithTarget)
	{
		setYRotation(yRot + y);
	}

}

void Camera::addTargetZRotation(float z)
{
	target->addZRotation(z);
	if (rotateWithTarget)
	{
		setZRotation(zRot + z);
	}
}


void Camera::setTargetDistance(float distance)
{
	if (distance < 0) { distance = 0;}
	if (distance > maxDistance) {distance = maxDistance;}
	targetDistance = distance;
	target->alpha = targetDistance / 100;
}
void Camera::addTargetDistance(float distance)
{
	setTargetDistance(targetDistance + distance);
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

void Camera::addXRotation(float angle)
{
	setXRotation(xRot + angle);

	if (rotateTarget)
	{
		alignTarget();
	}
}
void Camera::addYRotation(float angle)
{
	setYRotation(yRot + angle);
	if (rotateTarget)
	{
		alignTarget();
	}
}
void Camera::addZRotation(float angle)
{
	setZRotation( zRot + angle );
	if (rotateTarget)
	{
		alignTarget();
	}
}
