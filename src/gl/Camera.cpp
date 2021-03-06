#include "gl/Camera.hpp"

#include "gl/util.hpp"
#include <cassert>

#include <boost/math/constants/constants.hpp>
static const double PI = boost::math::constants::pi<double>();
static const double PI_2 = 2 * PI;

namespace nt {
namespace gl {

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
	setTarget(target);
}

void Camera::setTarget(Player* mob)
{
	assert(target != 0);
	mob->alpha(target->alpha());
	target->alpha(target->baseAlpha());
	target = mob;
	alignWithTarget();
}

// target rotates to face away from camera
void Camera::alignTarget()
{
	// camera and object xRots are off by 1/4 turn
	target->rotation().set(
		rotation().x() - PI_2,
		rotation().y(),
		rotation().z()
	);
}

// camera rotates to face at back of target
void Camera::alignWithTarget()
{
	// camera and object xRots are off by 1/4 turn
	setXRotation( target->rotation().x() + PI_2);
	setYRotation( target->rotation().y() );
	setZRotation( target->rotation().z() );

}

void Camera::addTargetXRotation(float x)
{
	target->rotation().addX(x);
}
void Camera::addTargetYRotation(float y)
{
	target->rotation().addY(y);
}

void Camera::addTargetZRotation(float z)
{
	target->rotation().addZ(z);
	if (rotateWithTarget)
	{
		setZRotation(rotation().z() + z);
	}
}


void Camera::setTargetDistance(float distance)
{
	if (distance < 0) { distance = 0;}
	if (distance > maxDistance) {distance = maxDistance;}
	targetDistance = distance;
	target->alpha(targetDistance / 100);
}
void Camera::addTargetDistance(float distance)
{
	setTargetDistance(targetDistance + distance);
}

	// XXX: This needs to rotate X first and then Z for the rotations to make sense
	// This is the opposite of the way we rotate objects
void Camera::applySettings()
{
	// distance the camera from the target
	glTranslatef( 0.0f,0.0f, -targetDistance);

	glRotateRadiansBackwards(rotation());

	// keeps the target in the center of the screen
	glTranslatef(
		-target->position().x(),
		-target->position().y(),
		-target->position().z()
	);

}
// XXX: don't know how to do this properly with vector3
void Camera::setXRotation(float angle)
{
	normalizeRadians(angle);
	// keep us from flipping upside down
	if ( angle > 3 * PI_2 ) { angle = 2 * PI; }
	else if ( angle > PI ) {angle = PI;}
	_rotation.setX(angle);
}

void Camera::setYRotation(float angle)
{
	_rotation.setY(angle);
}

void Camera::setZRotation(float angle)
{
	_rotation.setZ(angle);
}

void Camera::addXRotation(float angle)
{
	setXRotation(rotation().x() + angle);
	if (rotateTarget)
	{
		alignTarget();
	}
}
void Camera::addYRotation(float angle)
{
	_rotation.addY(angle);
	if (rotateTarget)
	{
		alignTarget();
	}
}
void Camera::addZRotation(float angle)
{
	_rotation.addZ(angle);
	if (rotateTarget)
	{
		alignTarget();
	}
}

} // namespace gl
} // namespace nt
