#ifndef VEHICLEGLWIDGET_H
#define VEHICLEGLWIDGET_H

#include <QGLWidget>
#include <QVector3D>
#include "MeasuredTimer.h"

struct Vehicle
{
	Vehicle() :
		velocity(0),
		angle(0)
	{
	}
	QVector3D pos;
	float velocity;
	float angle;
};

struct KeyPad
{
	bool accelerator;
	bool brake;
	bool left;
	bool right;
};

class VehicleGLWidget : public QGLWidget
{
	Q_OBJECT

	MeasuredTimer timer;
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
	void tick(const float& elapsed);
};

#endif // VEHICLEGLWIDGET_H
