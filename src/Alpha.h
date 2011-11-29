#ifndef ALPHA_H
#define ALPHA_H

#include <QGLWidget>
#include <QVector3D>
#include "MeasuredTimer.h"
#include <cmath>


struct Player
{
	Player() : velocity(0), svelocity(0), facing(M_PI / 2), pitch(0), roll(0), heading(0), defaultAlpha(1),
	alpha(defaultAlpha){}
	QVector3D pos;
	float velocity;
	float svelocity; // strafing right is positive
	float facing;
	float pitch;
	float roll;
	float heading; // Which direction the player is moving, such as strafing
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
// XXX: having issues implementing updateGL() from set(XYZ)Rotation

class Camera
{
public:
	Camera()
	{
		moveWithTarget = true;
		rotateWithTarget = true;
		rotateTarget = false;
		zoomSpeed = 5;
		zSpeed = 0.9;
		xSpeed = 0.7;
		targetDistance = 100;

	}
	//XXX: everything is public
	void setTarget(Player &mob)
	{
		target = &mob;
	}
	bool moveWithTarget;
	bool rotateWithTarget;
	bool rotateTarget;

	float zoomSpeed; // A multiplier
	float zSpeed; // a multiplier
	float xSpeed; // a multiplier

	Player *target;



	void setTargetDistance(float distance)
	{
		if (distance < 0) { distance = 0;}
		if (distance > 800) {distance = 800;}
		targetDistance = distance;
		target->alpha = targetDistance / 100;
	}
	float getTargetDistance() {return targetDistance;}

protected:
	float targetDistance; // Distance from the target
};
// TODO: Move xRot, yRot, zRot and related to a more camera related area
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
public slots:
	void setXRotation(float angle);
	void setYRotation(float angle);
	void setZRotation(float angle);
signals:
	void xRotationChanged(float angle);
	void yRotationChanged(float angle);
	void zRotationChanged(float angle);
protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	void alphaRotateCamera(float x, float y, float z);
	void applyRotation() const;
	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);

	void qNormalizeAngle(float &angle) const
	{
		while (angle < 0)
			angle += 360;
		while (angle > 360)
			angle -= 360;
	}

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
	float xRot;
	float yRot;
	float zRot;
	QPoint lastPos;
private slots:
	void tick(const float& elapsed);

};


#endif // ALPHA_H
