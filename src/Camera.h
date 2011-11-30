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
	// XXX: needs a default target so I can set the alpha in the correct spot
	// anytime it is changed
	void setTarget(Player* mob);
	void alignTarget();
	void alignWithTarget();

	bool moveWithTarget;
	bool rotateWithTarget;
	bool rotateTarget;

	float zoomSpeed; // A multiplier
	float zSpeed; // a multiplier
	float xSpeed; // a multiplier

	Player *target;

	void applySettings() const;

	void setMaxDistance(float distance)
	{
		maxDistance = distance >= 0 ? distance : 0;
	}
	void setTargetDistance(float distance);
	float getTargetDistance() {return targetDistance;}

	void setXRotation(float angle);
	void setYRotation(float angle);
	void setZRotation(float angle);

	float getXRotation()
	{
		return xRot - M_PI_2;
	}
	float getYRotation() {return yRot;}
	float getZRotation() {return zRot;}
protected:
	float targetDistance; // Distance from the target
	float maxDistance; // the maximum that you can zoom out
private:
	float xRot;
	float yRot;
	float zRot;
};

#endif // CAMERA_H
