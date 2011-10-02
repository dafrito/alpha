#ifndef GLDEMO_H
#define GLDEMO_H

#include <QGLWidget>

class GLDemo : public QGLWidget
{
	Q_OBJECT

public:
	GLDemo(QWidget *parent = 0);
	~GLDemo() {}

	QSize minimumSizeHint() const
	{
		return QSize(50, 50);
	}

	QSize sizeHint() const
	{
		return QSize(400, 400);
	}

protected:
	virtual void render()=0;
	virtual void initializeGL();
	virtual void resizeGL(int width, int height);

	void paintGL();
	void keyPressEvent(QKeyEvent *e);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

private:
	int xRot;
	int yRot;
	int zRot;
	QPoint lastPos;

	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);
};

#include <QApplication>
#include <QDesktopWidget>

static void setup_demo(GLDemo& demo)
{
	demo.resize(demo.sizeHint());
	int desktopArea = QApplication::desktop()->width() *
			QApplication::desktop()->height();
	int widgetArea = demo.width() * demo.height();
	if (((float)widgetArea / (float)desktopArea) < 0.75f)
		demo.show();
	else
		demo.showMaximized();
}

#endif // GLDEMO_H
