#ifndef ALPHA_H
#define ALPHA_H

#include <QGLWidget>
#include <QVector3D>
#include "MeasuredTimer.h"
#include <cmath>


struct Player
{
	Player() : velocity(0), svelocity(0), xRot(0), yRot(0), zRot(0), defaultAlpha(1),
	alpha(defaultAlpha){}
	QVector3D pos;
	float velocity;
	float svelocity; // strafing right is positive
	float xRot; // axis is left to right
	float yRot; // axis is down to up
	float zRot; // axis is back to front
	float defaultAlpha;
	float alpha;
};

// XXX: hardcoded keybinds
struct KeyBinds
{
	bool forward;
	bool backward;
	bool turnLeft;
	bool turnRight;
	bool strafeLeft;
	bool strafeRight;
	bool up;
	bool down;
	bool pitchup; // aim up
	bool pitchdown; // aim down

	bool leftMouse;	// mouse clicks
	bool rightMouse;

	bool F1;
	KeyBinds() :
	forward(false),
	backward(false),
	turnLeft(false),
	turnRight(false),
	strafeLeft(false),
	strafeRight(false),
	up(false),
	down(false),
	pitchup(false),
	pitchdown(false),
	leftMouse(false),
	rightMouse(false),
	F1(false)
	{};

};

// the beginning of a camera class
// XXX: most things are public
class Camera
{
public:
	Camera()
	{
		moveWithTarget = true;
		rotateWithTarget = true;
		rotateTarget = false;
		zoomSpeed = 5;
		zSpeed = 0.009;
		xSpeed = 0.007;
		targetDistance = 100;
		maxDistance = 800;

	}
	// XXX: needs a default target so I can set the alpha in the correct spot
	// anytime it is changed
	void setTarget(Player &mob)
	{
		//target->alpha = target->defaultAlpha;
		target = &mob;
		// camera faces what the target faces
		setXRotation(target->xRot + M_PI_2);
		setYRotation(target->yRot);
		setZRotation(target->zRot);

	}

	bool moveWithTarget;
	bool rotateWithTarget;
	bool rotateTarget;

	float zoomSpeed; // A multiplier
	float zSpeed; // a multiplier
	float xSpeed; // a multiplier

	Player *target;

	void applySettings() const
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

	void setMaxDistance(float distance)
	{
		maxDistance = distance >= 0 ? distance : 0;
	}
	void setTargetDistance(float distance)
	{
		if (distance < 0) { distance = 0;}
		if (distance > maxDistance) {distance = maxDistance;}
		targetDistance = distance;
		target->alpha = targetDistance / 100;
	}
	float getTargetDistance() {return targetDistance;}

	void setXRotation(float angle)
	{
		normalizeAngle(angle);
		// keep us from flipping upside down
		if ( angle > 3 * M_PI_2 ) { angle = 2 * M_PI; }
		else if ( angle > M_PI ) {angle = M_PI;}

		if (angle != xRot) {
			xRot = angle;
		}
	}

	void setYRotation(float angle)
	{
		normalizeAngle(angle);
		if (angle != yRot) {
			yRot = angle;
		}
	}

	void setZRotation(float angle)
	{
		normalizeAngle(angle);
		if (angle != zRot) {
			zRot = angle;

		}
	}
	float xRot;
	float yRot;
	float zRot;
protected:
	float targetDistance; // Distance from the target
	float maxDistance; // the maximum that you can zoom out
	void normalizeAngle(float &angle) const
	{
		while (angle < 0)
			angle += 2 * M_PI;
		while (angle > 2 * M_PI )
			angle -= 2 * M_PI;
	}
private:


};



class Alpha : public QGLWidget
{
	Q_OBJECT
	MeasuredTimer timer;
	KeyBinds pad;
	Player player;
	Player player2;
	Camera camera;



public:
	Alpha(QWidget* const parent = 0);
protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);


	void NewTarget()
	{
		if (camera.target == &player){
			camera.target->alpha = camera.target->defaultAlpha;
			camera.setTarget(player2);
		} else {
			camera.target->alpha = camera.target->defaultAlpha;
			camera.setTarget(player);
		}
	}
private:
	QPoint lastPos;
private slots:
	void tick(const float& elapsed);

};


#endif // ALPHA_H
