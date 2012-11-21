#ifndef CAMERA_H
#define CAMERA_H

#include "Player.h"
#include <cmath>

// the beginning of a camera class
// XXX: most things are public
class Camera
{
	typedef Vector3<float, WrapRadians> Rotation;

public:
	Camera(Player* t);
	void setTarget(Player* mob);
	// TODO: change the aligns to take a vector and modify that vector
	// that way we can align healthbars / text with the camera easily
	void alignTarget();
	void alignWithTarget();
	void addTargetXRotation(float x);
	void addTargetYRotation(float y);
	void addTargetZRotation(float z);

	Player *target;

	void applySettings();

	void setMaxDistance(float distance)
	{
		maxDistance = distance >= 0 ? distance : 0;
	}
	void setTargetDistance(float distance);
	void addTargetDistance(float distance);

	float getTargetDistance() {return targetDistance;}

	Rotation& rotation()
	{
		return _rotation;
	}

	void setXRotation(float angle);
	void setYRotation(float angle);
	void setZRotation(float angle);

	void addXRotation(float angle);
	void addYRotation(float angle);
	void addZRotation(float angle);

	float zoomSpeed; // A multiplier
	float zSpeed; // a multiplier
	float xSpeed; // a multiplier
	bool moveWithTarget;
	bool rotateWithTarget;
	bool rotateTarget;
protected:

	float targetDistance; // Distance from the target
	float maxDistance; // the maximum that you can zoom out

private:

	Rotation _rotation;

};

#endif // CAMERA_H
