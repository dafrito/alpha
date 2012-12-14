#ifndef ALPHA_H
#define ALPHA_H

#include <QGLWidget>

// Used for interpreting mouse input events
#include <QApplication>
#include <QDesktopWidget>

#include "MeasuredTimer.h"
#include "Player.h"
#include "Camera.h"
#include "PlayerInput.h"
#include "Cuboid.h"

class FTPolygonFont;

class Alpha : public QGLWidget
{
	Q_OBJECT

	MeasuredTimer timer;
	PlayerInput input;
	Player player;
	Player player2;
	Camera camera;
	QPoint lastPos;
	Cuboid playerShape;
	FTPolygonFont font;
	QCursor cursor; // can set custom shapes to this
	QPoint cursorHiddenAt;
	bool cursorShown;
	QRect _desktop; // _desktop.width() X _desktop.height() == resolution
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
	void hideCursor();
	void showCursor();
	QRect desktop()
	{
		return _desktop;
	}
	void NewTarget()
	{
		if (camera.target == &player){
			camera.setTarget(&player2);
		} else {
			camera.setTarget(&player);
		}
	}
	void drawCameraOrientedText(FTFont* const font, const char* text, int zOffset);


private slots:
	void tick(const float& elapsed);
};

#endif // ALPHA_H
