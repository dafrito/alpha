#ifndef ALPHA_H
#define ALPHA_H

#include <QGLWidget>
#include <QVector3D>
#include "MeasuredTimer.h"
#include <cmath>
#include "Player.h"
#include "Camera.h"
#include "PlayerInput.h"

class Alpha : public QGLWidget
{
	Q_OBJECT
	MeasuredTimer timer;
	PlayerInput input;
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
