#ifndef ALPHA_H
#define ALPHA_H

#include <QGLWidget>

// Used for interpreting mouse input events
#include <QApplication>
#include <QDesktopWidget>

#include "MeasuredTimer.hpp"
#include "Player.hpp"
#include "gl/Camera.hpp"
#include "PlayerInput.h"
#include "gl/Cuboid.hpp"

class FTPolygonFont;

namespace nt {

class Alpha : public QGLWidget
{
	Q_OBJECT

	MeasuredTimer timer;
	PlayerInput input;
	Player player;
	Player player2;
	gl::Camera camera;
	QPoint lastPos;
	gl::Cuboid playerShape;
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
	QRect desktop() { return _desktop; }
	void NewTarget()
	{
		if (camera.target == &player){
			camera.setTarget(&player2);
		} else {
			camera.setTarget(&player);
		}
	}

private slots:
	void tick(const double& elapsed);
};

void drawCameraOrientedText(const gl::Camera& camera, FTFont* const font, const char* text, int zOffset);

} // namespace nt

#endif // ALPHA_H
