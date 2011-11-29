#ifndef ALPHA_H
#define ALPHA_H

#include <QGLWidget>
#include <QVector3D>
#include "MeasuredTimer.h"
#include <cmath>

struct Player
{
	Player() : velocity(0), svelocity(0), facing(M_PI / 2), pitch(0), roll(0), heading(0),
	camRadius(100), camZoomSpeed(5), camSpeed(0.9),
	camFreeSpin(false),camRotatePlayer(false), camFollowPlayer(true){}
	QVector3D pos;
	float velocity;
	float svelocity; // strafing right is positive
	float facing;
	float pitch;
	float roll;
	float heading; // Which direction the player is moving, such as strafing
	// TODO: combine all the camera stuff, including (x,y,z)Rot
	float camRadius; // Distance from player
	float camZoomSpeed; // A multiplier
	float camSpeed; // a multiplier
	bool camFreeSpin; // Cam spins around player on mouse movements
	bool camRotatePlayer;
	bool camFollowPlayer;
	void limitCamRadius(float &radius ){
		if (radius < 0) { radius = 0;}
		if (radius > 800) {radius = 800;}
	}

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
	rightMouse(false)
	{};

};
// TODO: Move xRot, yRot, zRot and related to a more camera related area
class Alpha : public QGLWidget
{
	Q_OBJECT
	MeasuredTimer timer;
	KeyBinds pad;
	Player player;


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
	void applyRotation() const; // ???: what does the const after mean?
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
private:
	float xRot;
	float yRot;
	float zRot;
	QPoint lastPos;
private slots:
	void tick(const float& elapsed);

};


#endif // ALPHA_H
