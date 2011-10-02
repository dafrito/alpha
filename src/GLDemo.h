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

protected:
	virtual void render()=0;
	virtual void initializeGL();
	virtual void resizeGL(int width, int height);

	void paintGL();
	void keyPressEvent(QKeyEvent *e);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);
private:
	int xRot;
	int yRot;
	int zRot;
	QPoint lastPos;
};

#endif // GLDEMO_H
