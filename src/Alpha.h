#ifndef ALPHA_H
#define ALPHA_H

#include <QGLWidget>
#include <QVector3D>
#include "MeasuredTimer.h"

struct Player // ???: understand why these are made like this
{
	Player() : velocity(0), yaw(0), pitch(0), roll(0),
	camRadius(100), camZoomSpeed(5), camSpeed(0.9){}
	QVector3D pos;
	float velocity;
	float yaw;
	float pitch;
	float roll;
	float camRadius; // Distance from player
	float camZoomSpeed; // A multiplier
	float camSpeed; // a multiplier
};

// XXX: hardcoded keybinds
struct KeyBinds
{
	bool forward;
	bool backward;
	bool yawleft; //turn left
	bool yawright; // turn right
	bool up;
	bool down;
	bool pitchup; // aim up
	bool pitchdown; // aim down

	bool leftPress;	// mouse clicks
	bool rightPress;

	KeyBinds() :
	forward(false),
	backward(false),
	yawleft(false),
	yawright(false),
	up(false),
	down(false),
	pitchup(false),
	pitchdown(false),
	leftPress(false),
	rightPress(false)
	{};

};

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
