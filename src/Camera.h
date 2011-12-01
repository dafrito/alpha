#ifndef CAMERA_H
#define CAMERA_H

#include "Player.h"
#include <cmath>

// the beginning of a camera class
// XXX: most things are public
class Camera
{
public:
	Camera(Player* t);
	void setTarget(Player* mob);
	void alignTarget();
	void alignWithTarget();
	void addTargetXRotation(float x);
	void addTargetYRotation(float y);
	void addTargetZRotation(float z);

	Player *target;

	void applySettings() const;

	void setMaxDistance(float distance)
	{
		maxDistance = distance >= 0 ? distance : 0;
	}
	void setTargetDistance(float distance);
	void addTargetDistance(float distance);

	float getTargetDistance() {return targetDistance;}



	void setXRotation(float angle);
	void setYRotation(float angle);
	void setZRotation(float angle);

	void addXRotation(float angle);
	void addYRotation(float angle);
	void addZRotation(float angle);

	float getXRotation() { return xRot; }
	float getYRotation() { return yRot; }
	float getZRotation() { return zRot; }

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
	// TODO Ideally, these would be in a Vector3<float>
	float xRot;
	float yRot;
	float zRot;

};

#endif // CAMERA_H
