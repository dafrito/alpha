#ifndef ALPHA_H
#define ALPHA_H

#include <QGLWidget>
#include <QVector3D>
#include "MeasuredTimer.h"
#include <cmath>
#include "Player.h"
#include "Camera.h"

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
			camera.setTarget(&player2);
		} else {
			camera.setTarget(&player);
		}
	}
private:
	QPoint lastPos;
private slots:
	void tick(const float& elapsed);

};

#endif // ALPHA_H
