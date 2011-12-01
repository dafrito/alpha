#ifndef PLAYER_H
#define PLAYER_H

#include <QVector3D>
#include "Vector.h"
#include "util.h"

using namespace nt;

struct Player
{
	Player() : velocity(0,0,0), xRot(0), yRot(0), zRot(0), defaultAlpha(1),
	alpha(defaultAlpha){}
	// TODO Convert this to use Vector3<double>
	QVector3D pos;
	Vector3<double> velocity;
	void setVelocity(double x, double y, double z)
	{
		velocity.setX(x);
		velocity.setY(y);
		velocity.setZ(z);
	}
	// TODO Convert this to use Vector3<float>
	void setXRotation(float angle)
	{
		normalizeAngle(angle);
		xRot = angle;
	}

	void setYRotation(float angle)
	{
		normalizeAngle(angle);
		yRot = angle;
	}

	void setZRotation(float angle)
	{
		normalizeAngle(angle);
		zRot = angle;
	}

	void addXRotation(float angle) { setXRotation(xRot + angle); }
	void addYRotation(float angle) { setYRotation(yRot + angle); }
	void addZRotation(float angle) { setZRotation(zRot + angle); }

	float getXRotation() { return xRot; }
	float getYRotation() { return yRot; }
	float getZRotation() { return zRot; }

	float xRot; // axis is left to right
	float yRot; // axis is back to front
	float zRot; // axis is down to up
	float defaultAlpha;
	float alpha;
};

#endif // PLAYER_H
