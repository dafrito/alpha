#ifndef VEHICLEGLWIDGET_H
#define VEHICLEGLWIDGET_H

#include <QGLWidget>
#include <QVector3D>
#include "MeasuredTimer.hpp"

struct Vehicle
{
	Vehicle() :
		velocity(0),
		angle(0),
		maxspeed(1200),
		rev_maxspeed(-100)
	{
	}
	QVector3D pos;
	float velocity;
	float angle;
	float maxspeed;
	float rev_maxspeed;
};

struct KeyPad
{
	bool accelerator;
	bool brake;
	bool left;
	bool right;
	bool reverse;
	KeyPad() : accelerator(false), brake(false), left(false), right(false), reverse(false) {}
};

class VehicleGLWidget : public QGLWidget
{
	Q_OBJECT

	nt::MeasuredTimer timer;
	KeyPad pad;
	Vehicle car;
public:
	VehicleGLWidget(QWidget* const parent = 0);
protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);
private slots:
	void tick(const double& elapsed);
};

#endif // VEHICLEGLWIDGET_H
