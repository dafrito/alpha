#ifndef PLAYER_H
#define PLAYER_H

#include <QVector3D>

struct Player
{
	Player() : xRot(0), yRot(0), zRot(0), defaultAlpha(1),
	alpha(defaultAlpha){}
	// TODO Convert this to use Vector3<double>
	QVector3D pos;
	// TODO Convert this to use Vector3<float>
	float xRot; // axis is left to right
	float yRot; // axis is down to up
	float zRot; // axis is back to front
	float defaultAlpha;
	float alpha;
};

#endif // PLAYER_H
