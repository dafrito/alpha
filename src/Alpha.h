#ifndef ALPHA_H
#define ALPHA_H

#include <QGLWidget>
#include <QVector3D>
#include "MeasuredTimer.h"

struct Player //TODO: understand why these are made like this
{
	Player() : velocity(0), vvelocity(0), yaw(0), pitch(0), roll(0){}
	QVector3D pos;
	float velocity;
	float vvelocity; // XXX: need to combine into 1 true velocity
	float yaw;
	float pitch;
	float roll;
};

struct KeyBinds
{
	bool forward;
	bool backward;
	bool yawleft; //turn left
	bool yawright; // turn right
	bool up;
	bool down;
	bool pitchup; // aim down
	bool pitchdown; // aim down

	KeyBinds() :
	forward(false),
	backward(false),
	yawleft(false),
	yawright(false),
	up(false),
	down(false),
	pitchup(false),
	pitchdown(false)
	{}
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
	void setXRotation(int angle)
	{
		setScaledXRotation(angle * Alpha::ROTATION_SCALE);
	}

	void setYRotation(int angle)
	{
		setScaledYRotation(angle * Alpha::ROTATION_SCALE);
	}

	void setZRotation(int angle)
	{
		setScaledZRotation(angle * Alpha::ROTATION_SCALE);
	}

	void setScaledXRotation(int angle);
	void setScaledYRotation(int angle);
	void setScaledZRotation(int angle);
signals:
	void xRotationChanged(int angle);
	void yRotationChanged(int angle);
	void zRotationChanged(int angle);
protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	void applyRotation() const;
	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	// We scale rotation such that 1 unit of xRot, yRot, or zRot is
	// equal to 1/ROTATION_SCALE degrees. Therefore, when you want to
	// set rotation, you need to multiply by this scale to get expected
	// results:
	//
	// xRot = 45 * ROTATION_SCALE; // xRot is now 45 degrees
	static const int ROTATION_SCALE = 16;

	void qNormalizeAngle(int &angle) const
	{
		while (angle < 0)
			angle += 360 * Alpha::ROTATION_SCALE;
		while (angle > 360 * Alpha::ROTATION_SCALE)
			angle -= 360 * Alpha::ROTATION_SCALE;
	}
private:
	int xRot;
	int yRot;
	int zRot;
	QPoint lastPos;
private slots:
	void tick(const float& elapsed);

};


#endif // ALPHA_H
